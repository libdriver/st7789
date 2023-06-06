[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ST7789

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/st7789/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The ST7789 is a single-chip controller/driver for 262K-color, graphic type TFT-LCD. It consists of 720 source line and 320 gate line driving circuits. This chip is capable of connecting directly to an external microprocessor, and accepts, 8-bits/9-bits/16-bits/18-bits parallel interface. Display data can be stored in the on-chip display data RAM of 240x320x18 bits. It can perform display data RAM read/write operation with no external operation clock to minimize power consumption. In addition, because of the integrated power supply circuit necessary to drive liquid crystal; it is possible to make a display system with the fewest components.

LibDriver ST7789 is the full function driver of ST7789 launched by LibDriver.It provides the functions of drawing single point, filling block, image display, etc. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver ST7789 source files.

/interface includes LibDriver ST7789 SPI platform independent template.

/test includes LibDriver ST7789 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver ST7789 sample code.

/doc includes LibDriver ST7789 offline document.

/datasheet includes ST7789 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SPI platform independent template and finish your platform SPI driver.

Add /src, /interface and /example to your project.

### Usage

#### example basic

The image extraction format is as follows and color format is RGB565.

<div align=center>
<img src="/doc/image/image_format.svg" width="220" height="220"/>
</div>

```C
#include "driver_st7789_basic.h"
#include "driver_st7789_display_image.h"

uint8_t res;
uint32_t color = 65535;
uint16_t x0 = 0;
uint16_t x1 = 0;
uint16_t x2 = 16;
uint16_t y0 = 0;
uint16_t y1 = 0;
uint16_t y2 = 16;
char str[49] = "libdriver";

/* basic init */
res = st7789_basic_init();
if (res != 0)
{
    st7789_interface_debug_print("st7789: init failed.\n");

    return 1;
}

/* basic clear */
res = st7789_basic_clear();
if (res != 0)
{
    (void)st7789_basic_deinit();

    return 1;
}

...
    
/* basic display on */
res = st7789_basic_display_on();
if (res != 0)
{
    (void)st7789_basic_deinit();

    return 1;
}

...
    
/* show the string */
res = st7789_basic_string(0, 0, str, (uint16_t)strlen(str), color, ST7789_FONT_16);
if (res != 0)
{
    (void)st7789_basic_deinit();

    return 1;
}

...

/* write point */
res = st7789_basic_write_point(x0, y0, color);
if (res != 0)
{
    (void)st7789_basic_deinit();

    return 1;
}

...
    
/* basic rect */
res = st7789_basic_rect(x1, y1, x2, y2, color);
if (res != 0)
{
    (void)st7789_basic_deinit();

    return 1;
}

...
    
/* draw picture */
res = st7789_draw_picture_16bits(&gs_handle, 0, 0, 239, 319, (uint16_t *)gsc_image);
if (res != 0)
{
    (void)st7789_deinit(&gs_handle);

    return 1;
}

...
    
/* basic display off */
res = st7789_basic_display_off();
if (res != 0)
{
    (void)st7789_basic_deinit();

    return 1;
}

...
    
/* basic deinit */
res = st7789_basic_deinit();
if (res != 0)
{
    st7789_interface_debug_print("st7789: deinit failed.\n");

    return 1;
}

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/st7789/index.html](https://www.libdriver.com/docs/st7789/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved 



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please sent an e-mail to lishifenging@outlook.com.