// UTF-8 text drawing for PixelFonts (hand-written, not generated).
//
// Adafruit GFX print() sends single bytes, so the accented letters of the _extended_latin fonts (č œ ž ...) and the
// quotes „ “ ” ‚ ‘ ’ and € cannot be reached with it. pixelfonts::drawText() decodes UTF-8 and draws any glyph of a
// GFXfont, with the same cursor rules as print(): (x, y) is the left end of the baseline.
//
//   int16_t x = pixelfonts::drawText(display, &pixelfont_extended_latin_13x7_thin, 10, 30, "Teplota 23 °C, vlhkost 45 %", GxEPD_BLACK);
//   int16_t w = pixelfonts::textWidth(&pixelfont_extended_latin_13x7_thin, "Příliš žluťoučký kůň");
#pragma once
#include <Adafruit_GFX.h>

#ifndef pgm_read_ptr
#define pgm_read_ptr(addr) (*(const void *const *)(addr))
#endif

namespace pixelfonts {

// Next code point of a UTF-8 string (advances s). Invalid bytes are returned as they are.
inline uint32_t nextCodepoint(const char *&s) {
  uint8_t c = (uint8_t)*s++;
  if (c < 0x80) return c;
  int extra = (c & 0xE0) == 0xC0 ? 1 : (c & 0xF0) == 0xE0 ? 2 : (c & 0xF8) == 0xF0 ? 3 : 0;
  uint32_t cp = extra == 1 ? (c & 0x1F) : extra == 2 ? (c & 0x0F) : (c & 0x07);
  if (!extra) return c;
  for (int i = 0; i < extra; i++) {
    uint8_t n = (uint8_t)*s;
    if ((n & 0xC0) != 0x80) return c;  // truncated sequence
    cp = (cp << 6) | (n & 0x3F);
    s++;
  }
  return cp;
}

// „ “ ” ‚ ‘ ’ € sit at 0x83-0x89 in the fonts: their Unicode code points are far outside the fonts' range.
inline uint32_t fontCode(uint32_t cp) {
  switch (cp) {
    case 0x201E: return 0x83;
    case 0x201C: return 0x84;
    case 0x201D: return 0x85;
    case 0x201A: return 0x86;
    case 0x2018: return 0x87;
    case 0x2019: return 0x88;
    case 0x20AC: return 0x89;
  }
  return cp;
}

// Glyph of a code point, or nullptr if the font does not cover it.
inline const GFXglyph *glyphFor(const GFXfont *font, uint32_t cp) {
  cp = fontCode(cp);
  uint16_t first = pgm_read_word(&font->first), last = pgm_read_word(&font->last);
  if (cp < first || cp > last) return nullptr;
  return ((const GFXglyph *)pgm_read_ptr(&font->glyph)) + (cp - first);
}

// Width in pixels the cursor moves for this text (sum of xAdvance).
inline int16_t textWidth(const GFXfont *font, const char *text) {
  int16_t w = 0;
  while (*text) {
    const GFXglyph *g = glyphFor(font, nextCodepoint(text));
    if (g) w += pgm_read_byte(&g->xAdvance);
  }
  return w;
}

// Draws UTF-8 text with its baseline starting at (x, y). Returns the cursor x after the text.
inline int16_t drawText(Adafruit_GFX &gfx, const GFXfont *font, int16_t x, int16_t y, const char *text,
                        uint16_t color) {
  const uint8_t *bitmap = (const uint8_t *)pgm_read_ptr(&font->bitmap);
  gfx.startWrite();
  while (*text) {
    const GFXglyph *g = glyphFor(font, nextCodepoint(text));
    if (!g) continue;
    uint16_t bo = pgm_read_word(&g->bitmapOffset);
    uint8_t w = pgm_read_byte(&g->width), h = pgm_read_byte(&g->height);
    int8_t xo = (int8_t)pgm_read_byte(&g->xOffset), yo = (int8_t)pgm_read_byte(&g->yOffset);
    uint8_t bits = 0, bit = 0;
    for (uint8_t yy = 0; yy < h; yy++) {
      for (uint8_t xx = 0; xx < w; xx++) {
        if (!(bit++ & 7)) bits = pgm_read_byte(&bitmap[bo++]);
        if (bits & 0x80) gfx.writePixel(x + xo + xx, y + yo + yy, color);
        bits <<= 1;
      }
    }
    x += pgm_read_byte(&g->xAdvance);
  }
  gfx.endWrite();
  return x;
}

}  // namespace pixelfonts
