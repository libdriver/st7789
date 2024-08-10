[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ST7789

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/st7789/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ST7789是262K彩色图形型TFT-LCD的单片机控制器/驱动器。它由720个源极线和320个栅极线驱动电路组成。该芯片能够直接连接到外部微处理器，并接受8位/9位/16位/18位并行接口。显示数据可以存储在240x320x18位的片上显示数据RAM中。它可以在没有外部操作时钟的情况下执行显示数据RAM读/写操作，以最大限度地减少功耗。

LibDriver ST7789是LibDriver推出的ST7789的全功能驱动，该驱动提供绘制单点，填充块，图片显示等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver ST7789的源文件。

/interface目录包含了LibDriver ST7789与平台无关的SPI总线模板。

/test目录包含了LibDriver ST7789驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver ST7789编程范例。

/doc目录包含了LibDriver ST7789离线文档。

/datasheet目录包含了ST7789数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的SPI总线模板，完成指定平台的SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

图像提取格式如下，颜色格式是RGB565。

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

### 文档

在线文档: [https://www.libdriver.com/docs/st7789/index.html](https://www.libdriver.com/docs/st7789/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。