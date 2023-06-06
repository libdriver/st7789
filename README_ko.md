[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ST7789

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/st7789/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ST7789는 262K 컬러, 그래픽 타입 TFT-LCD용 단일 칩 컨트롤러/드라이버입니다. 720개의 소스 라인과 320개의 게이트 라인 구동 회로로 구성됩니다. 이 칩은 외부 마이크로프로세서에 직접 연결할 수 있으며 8비트/9비트/16비트/18비트 병렬 인터페이스를 수용합니다. 디스플레이 데이터는 240x320x18비트의 온칩 디스플레이 데이터 RAM에 저장할 수 있습니다. 외부 동작 클록 없이 디스플레이 데이터 RAM 읽기/쓰기 작업을 수행하여 전력 소모를 최소화할 수 있습니다. 또한 액정을 구동하는 데 필요한 통합 전원 공급 회로 때문에; 가장 적은 구성 요소로 디스플레이 시스템을 만드는 것이 가능합니다.

LibDriver ST7789는 LibDriver에서 출시한 ST7789의 전체 기능 드라이버입니다. 단일 점 그리기, 블록 채우기, 이미지 표시 등의 기능을 제공합니다. LibDriver는 MISRA와 호환됩니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver ST7789의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver ST7789용 플랫폼 독립적인 SPI버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver ST7789드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver ST7789프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver ST7789오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 ST7789데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인SPI버스 템플릿을 참조하여 지정된 플랫폼에 대한 SPI버스 드라이버를 완성하십시오.

/src 디렉토리, /interface 디렉토리 및 /example 디렉토리를 프로젝트에 추가하십시오.

### 사용

#### example basic

이미지 추출 형식은 다음과 같으며 색상 형식은 RGB565입니다.

<div align=center>
<img src="/doc/image/image_format.svg" width="220" height="220"/>
</div>

```c
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

### 문서

온라인 문서: [https://www.libdriver.com/docs/st7789/index.html](https://www.libdriver.com/docs/st7789/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.