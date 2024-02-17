[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ST7789

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/st7789/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ST7789 は、262K 色のグラフィック タイプ TFT-LCD 用のシングルチップ コントローラ/ドライバです。 720本のソース線駆動回路と320本のゲート線駆動回路で構成されています。 このチップは外部マイクロプロセッサに直接接続でき、8 ビット/9 ビット/16 ビット/18 ビットのパラレル インターフェイスを受け入れます。 表示データは240×320×18ビットの内蔵表示データRAMに保存できます。 外部動作クロックなしで表示データRAMの読み出し/書き込み動作を行うことができ、消費電力を最小限に抑えます。 また、液晶駆動に必要な電源回路を内蔵しているため、 最小限のコンポーネントでディスプレイ システムを作成することが可能です。

LibDriver ST7789 は、LibDriver によって起動された ST7789 のフル機能ドライバです。単一点の描画、ブロックの塗りつぶし、画像表示などの機能を提供します。LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver ST7789のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver ST7789用のプラットフォームに依存しないSPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver ST7789ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver ST7789プログラミング例が含まれています。

/ docディレクトリには、LibDriver ST7789オフラインドキュメントが含まれています。

/ datasheetディレクトリには、ST7789データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSPIバステンプレートを参照して、指定したプラットフォームのSPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

画像抽出フォーマットは以下の通りで、カラーフォーマットはRGB565です。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/st7789/index.html](https://www.libdriver.com/docs/st7789/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。