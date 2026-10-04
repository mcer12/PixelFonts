![PixelFonts - Pixel fonts for tiny displays](images/title.png)

**PixelFont** is a family of **AdafruitGFX & u8g2 compatible** fonts, **hand crafted for tiny low-res displays**. The fonts are designed
to be **slender and condensed** to fit as much text on a line as possible. And to also look awesome.

You can also use AI to scale the fonts up, add spacing between pixels, makes pixels larger, rounded etc. So it’s a great way to make a faux-low-res display or a retro arcade kind of look.

## Language support

Supported languages are: **English, Spanish, French, Italian, Czech** and more. 

NOTE 1: Accented characters are available for **lowercase letters only** - capital letters with accents are not included as this requires modification of the letters.

NOTE 2: I have personally hand-crafted only the Czech special characters. Other extended Latin glyphs are AI generated, so PRs with corrections from native speakers are welcome!

## Usage

### AdafruitGFX

There are two options for each font - **english version**, which works with basic AdafruitGFX library and **extended latin version** which requires **[UTF-8 fork of AdafruitGFX](https://github.com/DoomHammer/Adafruit-GFX-Library/tree/enable-utf-8)**. 

Using extended latin version with standard library still works for english glyphs but because of extra data, it's taking more memory space, so it's recommended to use english version with it.

```cpp
#include <Adafruit_GFX.h>
#include <PixelFonts.h>   // every font; the ones you do not use take no flash

// This is required to make extended latin work, using forked Adafruit-GFX is required:
// https://github.com/DoomHammer/Adafruit-GFX-Library/tree/enable-utf-8
// Remove this line with stock AdafruitGFX and english font variants
display.utf8(true);

display.setFont(&pixelfont_extended_latin_13x7_semibold);
display.setTextColor(BLACK);
display.setCursor(10, 30);
display.print("Temperature 23.5");
```

**Scaling up for a low-res look:** `setTextSize()` draws every font pixel as a square block, so a small font turns
into big, chunky pixel text with no extra flash:

```cpp
display.setFont(&pixelfont_9x5_thin);
display.setTextSize(3);   // each font pixel becomes a 3x3 block: 27 px tall capitals
display.setCursor(0, 40);
display.print("23.5");
```

`setTextSize(x, y)` scales width and height separately; the line height scales with it.

### u8g2

The same fonts in **u8g2 format**: the font name + `_u8g2`. You can use english fonts or extended latin fonts with no limitations.

```cpp
#include <U8g2lib.h>
#include <PixelFontsU8g2.h>   // every u8g2 font; the ones you do not use take no flash

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

u8g2.begin();
u8g2.setFontMode(1);
u8g2.setFont(pixelfont_13x7_semibold_u8g2);
u8g2.drawStr(0, 20, "Temperature 23.5");
u8g2.setFont(pixelfont_extended_latin_13x7_semibold_u8g2);
u8g2.drawUTF8(0, 20 + PIXELFONT_EXTENDED_LATIN_13X7_SEMIBOLD_U8G2_LINE_HEIGHT, "Příliš žluťoučký kůň");
u8g2.sendBuffer();
```

Each u8g2 font comes with its line height, e.g. `PIXELFONT_13X7_SEMIBOLD_U8G2_LINE_HEIGHT`.

### BDF

The `bdf/` folder has **every font as a BDF file** (Unicode encoded), for u8g2's `bdfconv`, FontForge, the LVGL font
converter and other tools. `FONT_ASCENT` + `FONT_DESCENT` is the line height.

## Fonts

Names follow `pixelfont[_3d | _3d_condensed][_extended_latin]_ROWSxCOLS_WEIGHT`:

- `ROWSxCOLS` - size of the letter grid in pixels: capital height x capital width
- `WEIGHT` - stroke width: `thin` = 1px, `semibold` = 2px, `bold` = 3px
- `_3d` - outline + shadow version, 3 px taller, 1 px gap between characters and lines
- `_3d_condensed` - the same 3D version with no gap between characters and lines
- `_extended_latin` - adds the accented lowercase letters and punctuation (see Language support)

In the table: **Height** = pixel height of the capitals (3D versions include the outline and shadow), **Weight** =
stroke width, **English** = ASCII only, **Extended Latin** = ASCII + accented letters.

### ![Basic fonts](images/basic.png)

| Height | Weight | English | Extended Latin |
|---|---|---|---|
| 5 px | 1px | `pixelfont_5x5_thin` | - |
| 7 px | 1px | `pixelfont_7x5_thin` | `pixelfont_extended_latin_7x5_thin` |
| 9 px | 1px | `pixelfont_9x5_thin` | `pixelfont_extended_latin_9x5_thin` |
| 11 px | 1px | `pixelfont_11x5_thin` | `pixelfont_extended_latin_11x5_thin` |
| 13 px | 1px | `pixelfont_13x5_thin` | `pixelfont_extended_latin_13x5_thin` |
| 13 px | 1px | `pixelfont_13x7_thin` | `pixelfont_extended_latin_13x7_thin` |
| 13 px | 2px | `pixelfont_13x7_semibold` | `pixelfont_extended_latin_13x7_semibold` |
| 15 px | 1px | `pixelfont_15x5_thin` | `pixelfont_extended_latin_15x5_thin` |
| 15 px | 2px | `pixelfont_15x5_semibold` | `pixelfont_extended_latin_15x5_semibold` |
| 15 px | 1px | `pixelfont_15x7_thin` | `pixelfont_extended_latin_15x7_thin` |
| 15 px | 2px | `pixelfont_15x7_semibold` | `pixelfont_extended_latin_15x7_semibold` |
| 17 px | 1px | `pixelfont_17x5_thin` | `pixelfont_extended_latin_17x5_thin` |
| 17 px | 2px | `pixelfont_17x5_semibold` | `pixelfont_extended_latin_17x5_semibold` |
| 17 px | 1px | `pixelfont_17x7_thin` | `pixelfont_extended_latin_17x7_thin` |
| 17 px | 2px | `pixelfont_17x7_semibold` | `pixelfont_extended_latin_17x7_semibold` |
| 17 px | 3px | `pixelfont_17x7_bold` | `pixelfont_extended_latin_17x7_bold` |
| 21 px | 1px | `pixelfont_21x11_thin` | `pixelfont_extended_latin_21x11_thin` |
| 21 px | 3px | `pixelfont_21x11_bold` | `pixelfont_extended_latin_21x11_bold` |

### ![3D fonts](images/3d.png)

| Height | Weight | English | Extended Latin |
|---|---|---|---|
| 8 px | 1px | `pixelfont_3d_5x5_thin` | - |
| 8 px | 1px | `pixelfont_3d_condensed_5x5_thin` | - |
| 10 px | 1px | `pixelfont_3d_7x5_thin` | `pixelfont_3d_extended_latin_7x5_thin` |
| 10 px | 1px | `pixelfont_3d_condensed_7x5_thin` | `pixelfont_3d_condensed_extended_latin_7x5_thin` |
| 12 px | 1px | `pixelfont_3d_9x5_thin` | `pixelfont_3d_extended_latin_9x5_thin` |
| 12 px | 1px | `pixelfont_3d_condensed_9x5_thin` | `pixelfont_3d_condensed_extended_latin_9x5_thin` |
| 14 px | 1px | `pixelfont_3d_11x5_thin` | `pixelfont_3d_extended_latin_11x5_thin` |
| 14 px | 1px | `pixelfont_3d_condensed_11x5_thin` | `pixelfont_3d_condensed_extended_latin_11x5_thin` |
| 16 px | 1px | `pixelfont_3d_13x5_thin` | `pixelfont_3d_extended_latin_13x5_thin` |
| 16 px | 1px | `pixelfont_3d_condensed_13x5_thin` | `pixelfont_3d_condensed_extended_latin_13x5_thin` |
| 16 px | 1px | `pixelfont_3d_13x7_thin` | `pixelfont_3d_extended_latin_13x7_thin` |
| 16 px | 1px | `pixelfont_3d_condensed_13x7_thin` | `pixelfont_3d_condensed_extended_latin_13x7_thin` |
| 16 px | 2px | `pixelfont_3d_13x7_semibold` | `pixelfont_3d_extended_latin_13x7_semibold` |
| 16 px | 2px | `pixelfont_3d_condensed_13x7_semibold` | `pixelfont_3d_condensed_extended_latin_13x7_semibold` |
| 18 px | 1px | `pixelfont_3d_15x5_thin` | `pixelfont_3d_extended_latin_15x5_thin` |
| 18 px | 1px | `pixelfont_3d_condensed_15x5_thin` | `pixelfont_3d_condensed_extended_latin_15x5_thin` |
| 18 px | 2px | `pixelfont_3d_15x5_semibold` | `pixelfont_3d_extended_latin_15x5_semibold` |
| 18 px | 2px | `pixelfont_3d_condensed_15x5_semibold` | `pixelfont_3d_condensed_extended_latin_15x5_semibold` |
| 18 px | 1px | `pixelfont_3d_15x7_thin` | `pixelfont_3d_extended_latin_15x7_thin` |
| 18 px | 1px | `pixelfont_3d_condensed_15x7_thin` | `pixelfont_3d_condensed_extended_latin_15x7_thin` |
| 18 px | 2px | `pixelfont_3d_15x7_semibold` | `pixelfont_3d_extended_latin_15x7_semibold` |
| 18 px | 2px | `pixelfont_3d_condensed_15x7_semibold` | `pixelfont_3d_condensed_extended_latin_15x7_semibold` |
| 20 px | 1px | `pixelfont_3d_17x5_thin` | `pixelfont_3d_extended_latin_17x5_thin` |
| 20 px | 1px | `pixelfont_3d_condensed_17x5_thin` | `pixelfont_3d_condensed_extended_latin_17x5_thin` |
| 20 px | 2px | `pixelfont_3d_17x5_semibold` | `pixelfont_3d_extended_latin_17x5_semibold` |
| 20 px | 2px | `pixelfont_3d_condensed_17x5_semibold` | `pixelfont_3d_condensed_extended_latin_17x5_semibold` |
| 20 px | 1px | `pixelfont_3d_17x7_thin` | `pixelfont_3d_extended_latin_17x7_thin` |
| 20 px | 1px | `pixelfont_3d_condensed_17x7_thin` | `pixelfont_3d_condensed_extended_latin_17x7_thin` |
| 20 px | 2px | `pixelfont_3d_17x7_semibold` | `pixelfont_3d_extended_latin_17x7_semibold` |
| 20 px | 2px | `pixelfont_3d_condensed_17x7_semibold` | `pixelfont_3d_condensed_extended_latin_17x7_semibold` |
| 20 px | 3px | `pixelfont_3d_17x7_bold` | `pixelfont_3d_extended_latin_17x7_bold` |
| 20 px | 3px | `pixelfont_3d_condensed_17x7_bold` | `pixelfont_3d_condensed_extended_latin_17x7_bold` |
| 24 px | 1px | `pixelfont_3d_21x11_thin` | `pixelfont_3d_extended_latin_21x11_thin` |
| 24 px | 1px | `pixelfont_3d_condensed_21x11_thin` | `pixelfont_3d_condensed_extended_latin_21x11_thin` |
| 24 px | 3px | `pixelfont_3d_21x11_bold` | `pixelfont_3d_extended_latin_21x11_bold` |
| 24 px | 3px | `pixelfont_3d_condensed_21x11_bold` | `pixelfont_3d_condensed_extended_latin_21x11_bold` |

## Notes
Glyph data in a simple txt form is included, so you can use AI to generate any bitmap / font format.