[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ST7789

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/st7789/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der ST7789 ist ein Single-Chip-Controller/Treiber für 262K-Farb-TFT-LCD-Grafikkarten. Es besteht aus 720 Source-Leitungs- und 320 Gate-Leitungs-Treiberschaltungen. Dieser Chip kann direkt an einen externen Mikroprozessor angeschlossen werden und akzeptiert 8-Bit-/9-Bit-/16-Bit-/18-Bit-Parallelschnittstellen. Anzeigedaten können im On-Chip-Anzeigedaten-RAM mit 240 x 320 x 18 Bit gespeichert werden. Es kann Lese-/Schreibvorgänge im RAM für Anzeigedaten ohne externen Betriebstakt ausführen, um den Stromverbrauch zu minimieren. Aufgrund der integrierten Stromversorgungsschaltung, die zum Ansteuern von Flüssigkristallen erforderlich ist; Es ist möglich, ein Anzeigesystem mit den wenigsten Komponenten herzustellen.

LibDriver ST7789 ist der von LibDriver gestartete Vollfunktionstreiber von ST7789. Er bietet die Funktionen zum Zeichnen einzelner Punkte, zum Füllen von Blöcken, zur Bildanzeige usw. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver ST7789-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver ST7789 SPI.

/test enthält den Testcode des LibDriver ST7789-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver ST7789-Beispielcode.

/doc enthält das LibDriver ST7789-Offlinedokument.

/Datenblatt enthält ST7789-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

Das Bildextraktionsformat ist wie folgt und das Farbformat ist RGB565.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/st7789/index.html](https://www.libdriver.com/docs/st7789/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.