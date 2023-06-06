/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_st7789.h
 * @brief     driver st7789 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2023-04-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2023/04/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_ST7789_H
#define DRIVER_ST7789_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup st7789_driver st7789 driver function
 * @brief    st7789 driver modules
 * @{
 */

/**
 * @addtogroup st7789_basic_driver
 * @{
 */

/**
 * @brief st7789 buffer size definition
 */
#ifndef ST7789_BUFFER_SIZE
    #define ST7789_BUFFER_SIZE    (4096)        /**< 4096 */
#endif

/**
 * @brief st7789 bool enumeration definition
 */
typedef enum
{
    ST7789_BOOL_FALSE = 0x00,        /**< false */
    ST7789_BOOL_TRUE  = 0x01,        /**< true */
} st7789_bool_t;

/**
 * @brief st7789 font size enumeration definition
 */
typedef enum
{
    ST7789_FONT_12 = 0x0C,        /**< font 12 */
    ST7789_FONT_16 = 0x10,        /**< font 16 */
    ST7789_FONT_24 = 0x18,        /**< font 24 */
} st7789_font_t;

/**
 * @brief st7789 gamma curve enumeration definition
 */
typedef enum
{
    ST7789_GAMMA_CURVE_1 = 0x1,        /**< g2.2 */
    ST7789_GAMMA_CURVE_2 = 0x2,        /**< g1.8 */
    ST7789_GAMMA_CURVE_3 = 0x4,        /**< g2.5 */
    ST7789_GAMMA_CURVE_4 = 0x8,        /**< g1.0 */
} st7789_gamma_curve_t;

/**
 * @brief st7789 tearing effect enumeration definition
 */
typedef enum
{
    ST7789_TEARING_EFFECT_V_BLANKING                = 0x0,        /**< v-blanking */
    ST7789_TEARING_EFFECT_V_BLANKING_AND_H_BLANKING = 0x1,        /**< v-blanking and h-blanking */
} st7789_tearing_effect_t;

/**
 * @brief st7789 order enumeration definition
 */
typedef enum
{
    ST7789_ORDER_PAGE_TOP_TO_BOTTOM    = (0 << 7),        /**< top to bottom */
    ST7789_ORDER_PAGE_BOTTOM_TO_TOP    = (1 << 7),        /**< bottom to top */
    ST7789_ORDER_COLUMN_LEFT_TO_RIGHT  = (0 << 6),        /**< left to right */
    ST7789_ORDER_COLUMN_RIGHT_TO_LEFT  = (1 << 6),        /**< right to left */
    ST7789_ORDER_PAGE_COLUMN_NORMAL    = (0 << 5),        /**< normal mode */
    ST7789_ORDER_PAGE_COLUMN_REVERSE   = (1 << 5),        /**< reverse mode */
    ST7789_ORDER_LINE_TOP_TO_BOTTOM    = (0 << 4),        /**< lcd refresh top to bottom */
    ST7789_ORDER_LINE_BOTTOM_TO_TOP    = (1 << 4),        /**< lcd refresh bottom to top */
    ST7789_ORDER_COLOR_RGB             = (0 << 3),        /**< rgb */
    ST7789_ORDER_COLOR_BGR             = (1 << 3),        /**< bgr */
    ST7789_ORDER_REFRESH_LEFT_TO_RIGHT = (0 << 2),        /**< lcd refresh left to right */
    ST7789_ORDER_REFRESH_RIGHT_TO_LEFT = (1 << 2),        /**< lcd refresh right to left */
} st7789_order_t;

/**
 * @brief st7789 rgb interface color format enumeration definition
 */
typedef enum
{
    ST7789_RGB_INTERFACE_COLOR_FORMAT_65K  = 0x5,        /**< 65k of rgb interface */
    ST7789_RGB_INTERFACE_COLOR_FORMAT_262K = 0x6,        /**< 262k of rgb interface */
} st7789_rgb_interface_color_format_t;

/**
 * @brief st7789 control interface color format enumeration definition
 */
typedef enum
{
    ST7789_CONTROL_INTERFACE_COLOR_FORMAT_12_BIT = 0x3,        /**< 12bit/pixel */
    ST7789_CONTROL_INTERFACE_COLOR_FORMAT_16_BIT = 0x5,        /**< 16bit/pixel */
    ST7789_CONTROL_INTERFACE_COLOR_FORMAT_18_BIT = 0x6,        /**< 18bit/pixel */
} st7789_control_interface_color_format_t;

/**
 * @brief st7789 color enhancement mode enumeration definition
 */
typedef enum
{
    ST7789_COLOR_ENHANCEMENT_MODE_OFF            = 0x0,        /**< off */
    ST7789_COLOR_ENHANCEMENT_MODE_USER_INTERFACE = 0x1,        /**< user interface mode */
    ST7789_COLOR_ENHANCEMENT_MODE_STILL_PICTURE  = 0x2,        /**< still picture */
    ST7789_COLOR_ENHANCEMENT_MODE_MOVING_IMAGE   = 0x3,        /**< moving image */
} st7789_color_enhancement_mode_t;

/**
 * @brief st7789 color enhancement level enumeration definition
 */
typedef enum
{
    ST7789_COLOR_ENHANCEMENT_LEVEL_LOW    = 0x0,        /**< low enhancement */
    ST7789_COLOR_ENHANCEMENT_LEVEL_MEDIUM = 0x1,        /**< medium enhancement */
    ST7789_COLOR_ENHANCEMENT_LEVEL_HIGH   = 0x3,        /**< high enhancement */
} st7789_color_enhancement_level_t;

/**
 * @}
 */

/**
 * @addtogroup st7789_advance_driver
 * @{
 */

/**
 * @brief st7789 ram access enumeration definition
 */
typedef enum
{
    ST7789_RAM_ACCESS_MCU = 0x0,        /**< mcu interface */
    ST7789_RAM_ACCESS_RGB = 0x1,        /**< rgb interface */
} st7789_ram_access_t;

/**
 * @brief st7789 display mode enumeration definition
 */
typedef enum
{
    ST7789_DISPLAY_MODE_MCU   = 0x0,        /**< mcu interface */
    ST7789_DISPLAY_MODE_RGB   = 0x1,        /**< rgb interface */
    ST7789_DISPLAY_MODE_VSYNC = 0x2,        /**< vsync interface */
} st7789_display_mode_t;

/**
 * @brief st7789 data mode enumeration definition
 */
typedef enum
{
    ST7789_DATA_MODE_MSB = 0x0,        /**< big endian */
    ST7789_DATA_MODE_LSB = 0x1,        /**< little endian */
} st7789_data_mode_t;

/**
 * @brief st7789 rgb bus width enumeration definition
 */
typedef enum
{
    ST7789_RGB_BUS_WIDTH_18_BIT = 0x0,        /**< 18 bit bus width */
    ST7789_RGB_BUS_WIDTH_6_BIT  = 0x1,        /**< 6 bit bus width */
} st7789_rgb_bus_width_t;

/**
 * @brief st7789 frame type enumeration definition
 */
typedef enum
{
    ST7789_FRAME_TYPE_0 = 0x0,        /**< type0 */
    ST7789_FRAME_TYPE_1 = 0x1,        /**< type1 */
    ST7789_FRAME_TYPE_2 = 0x2,        /**< type2 */
    ST7789_FRAME_TYPE_3 = 0x3,        /**< type3 */
} st7789_frame_type_t;

/**
 * @brief st7789 pixel type enumeration definition
 */
typedef enum
{
    ST7789_PIXEL_TYPE_0 = 0x0,        /**< type0 */
    ST7789_PIXEL_TYPE_1 = 0x0,        /**< type1 */
    ST7789_PIXEL_TYPE_2 = 0x0,        /**< type2 */
    ST7789_PIXEL_TYPE_3 = 0x0,        /**< type3 */
} st7789_pixel_type_t;

/**
 * @brief st7789 direct rgb mode enumeration definition
 */
typedef enum
{
    ST7789_DIRECT_RGB_MODE_MEM   = 0x0,        /**< memory mode */
    ST7789_DIRECT_RGB_MODE_SHIFT = 0x1,        /**< shift register mode */
} st7789_direct_rgb_mode_t;

/**
 * @brief st7789 rgb if enable mode enumeration definition
 */
typedef enum
{
    ST7789_RGB_IF_ENABLE_MODE_MCU = 0x0,        /**< memory mode */
    ST7789_RGB_IF_ENABLE_MODE_DE  = 0x2,        /**< rgb de mode */
    ST7789_RGB_IF_ENABLE_MODE_HV  = 0x3,        /**< rgb hv mode */
} st7789_rgb_if_enable_mode_t;

/**
 * @brief st7789 pin level enumeration definition
 */
typedef enum
{
    ST7789_PIN_LEVEL_LOW  = 0x0,        /**< low active */
    ST7789_PIN_LEVEL_HIGH = 0x1,        /**< high active */
} st7789_pin_level_t;

/**
 * @brief st7789 frame rate divided control enumeration definition
 */
typedef enum
{
    ST7789_FRAME_RATE_DIVIDED_CONTROL_DIV_1 = 0x0,        /**< divide by 1 */
    ST7789_FRAME_RATE_DIVIDED_CONTROL_DIV_2 = 0x1,        /**< divide by 2 */
    ST7789_FRAME_RATE_DIVIDED_CONTROL_DIV_4 = 0x2,        /**< divide by 4 */
    ST7789_FRAME_RATE_DIVIDED_CONTROL_DIV_8 = 0x3,        /**< divide by 8 */
} st7789_frame_rate_divided_control_t;

/**
 * @brief st7789 inversion idle mode enumeration definition
 */
typedef enum
{
    ST7789_INVERSION_IDLE_MODE_DOT    = 0x0,        /**< dot inversion */
    ST7789_INVERSION_IDLE_MODE_COLUMN = 0x7,        /**< column inversion */
} st7789_inversion_idle_mode_t;

/**
 * @brief st7789 inversion partial mode enumeration definition
 */
typedef enum
{
    ST7789_INVERSION_PARTIAL_MODE_DOT    = 0x0,        /**< dot inversion */
    ST7789_INVERSION_PARTIAL_MODE_COLUMN = 0x7,        /**< column inversion */
} st7789_inversion_partial_mode_t;

/**
 * @brief st7789 non display source output level enumeration definition
 */
typedef enum
{
    ST7789_NON_DISPLAY_SOURCE_OUTPUT_LEVEL_V63 = 0x0,        /**< v63 */
    ST7789_NON_DISPLAY_SOURCE_OUTPUT_LEVEL_V0  = 0x1,        /**< v0 */
} st7789_non_display_source_output_level_t;

/**
 * @brief st7789 non display area scan mode enumeration definition
 */
typedef enum
{
    ST7789_NON_DISPLAY_AREA_SCAN_MODE_NORMAL   = 0x0,        /**< normal mode */
    ST7789_NON_DISPLAY_AREA_SCAN_MODE_INTERVAL = 0x1,        /**< interval scan mode */
} st7789_non_display_area_scan_mode_t;

/**
 * @brief st7789 non display frame frequency enumeration definition
 */
typedef enum
{
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_EVERY    = 0x0,        /**< every frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_3  = 0x1,        /**< 1/3 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_5  = 0x2,        /**< 1/5 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_7  = 0x3,        /**< 1/7 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_9  = 0x4,        /**< 1/9 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_11 = 0x5,        /**< 1/11 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_13 = 0x6,        /**< 1/13 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_15 = 0x7,        /**< 1/15 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_17 = 0x8,        /**< 1/17 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_19 = 0x9,        /**< 1/19 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_21 = 0xA,        /**< 1/21 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_23 = 0xB,        /**< 1/23 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_25 = 0xC,        /**< 1/25 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_27 = 0xD,        /**< 1/27 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_29 = 0xE,        /**< 1/29 frame */
    ST7789_NON_DISPLAY_FRAME_FREQUENCY_1_DIV_31 = 0xF,        /**< 1/31 frame */
} st7789_non_display_frame_frequency_t;

/**
 * @brief st7789 vghs enumeration definition
 */
typedef enum
{
    ST7789_VGHS_12P20_V = 0x0,        /**< 12.20V */
    ST7789_VGHS_12P54_V = 0x1,        /**< 12.54V */
    ST7789_VGHS_12P89_V = 0x2,        /**< 12.89V */
    ST7789_VGHS_13P26_V = 0x3,        /**< 13.26V */
    ST7789_VGHS_13P65_V = 0x4,        /**< 13.65V */
    ST7789_VGHS_14P06_V = 0x5,        /**< 14.06V */
    ST7789_VGHS_14P50_V = 0x6,        /**< 14.50V */
    ST7789_VGHS_14P97_V = 0x7,        /**< 14.97V */
} st7789_vghs_t;

/**
 * @brief st7789 vgls enumeration definition
 */
typedef enum
{
    ST7789_VGLS_NEGATIVE_7P16  = 0x0,        /**< -7.16V */
    ST7789_VGLS_NEGATIVE_7P67  = 0x1,        /**< -7.67V */
    ST7789_VGLS_NEGATIVE_8P23  = 0x2,        /**< -8.23V */
    ST7789_VGLS_NEGATIVE_8P87  = 0x3,        /**< -8.87V */
    ST7789_VGLS_NEGATIVE_9P60  = 0x4,        /**< -9.60V */
    ST7789_VGLS_NEGATIVE_10P43 = 0x5,        /**< -10.43V */
    ST7789_VGLS_NEGATIVE_11P38 = 0x6,        /**< -11.38V */
    ST7789_VGLS_NEGATIVE_12P50 = 0x7,        /**< -12.50V */
} st7789_vgls_t;

/**
 * @brief st7789 vdv vrh from enumeration definition
 */
typedef enum
{
    ST7789_VDV_VRH_FROM_NVM = 0x0,        /**< from nvm */
    ST7789_VDV_VRH_FROM_CMD = 0x1,        /**< from command write */
} st7789_vdv_vrh_from_t;

/**
 * @brief st7789 inversion selection enumeration definition
 */
typedef enum
{
    ST7789_INVERSION_SELECTION_DOT    = 0x0,        /**< dot inversion */
    ST7789_INVERSION_SELECTION_COLUMN = 0x7,        /**< column inversion */
} st7789_inversion_selection_t;

/**
 * @brief st7789 frame rate enumeration definition
 */
typedef enum
{
    ST7789_FRAME_RATE_119_HZ = 0x00,       /**< 119Hz */
    ST7789_FRAME_RATE_111_HZ = 0x01,       /**< 111Hz */
    ST7789_FRAME_RATE_105_HZ = 0x02,       /**< 105Hz */
    ST7789_FRAME_RATE_99_HZ  = 0x03,       /**< 99Hz */
    ST7789_FRAME_RATE_94_HZ  = 0x04,       /**< 94Hz */
    ST7789_FRAME_RATE_90_HZ  = 0x05,       /**< 90Hz */
    ST7789_FRAME_RATE_86_HZ  = 0x06,       /**< 86Hz */
    ST7789_FRAME_RATE_82_HZ  = 0x07,       /**< 82Hz */
    ST7789_FRAME_RATE_78_HZ  = 0x08,       /**< 78Hz */
    ST7789_FRAME_RATE_75_HZ  = 0x09,       /**< 75Hz */
    ST7789_FRAME_RATE_72_HZ  = 0x0A,       /**< 72Hz */
    ST7789_FRAME_RATE_69_HZ  = 0x0B,       /**< 69Hz */
    ST7789_FRAME_RATE_67_HZ  = 0x0C,       /**< 67Hz */
    ST7789_FRAME_RATE_64_HZ  = 0x0D,       /**< 64Hz */
    ST7789_FRAME_RATE_62_HZ  = 0x0E,       /**< 62Hz */
    ST7789_FRAME_RATE_60_HZ  = 0x0F,       /**< 60Hz */
    ST7789_FRAME_RATE_58_HZ  = 0x10,       /**< 58Hz */
    ST7789_FRAME_RATE_57_HZ  = 0x11,       /**< 57Hz */
    ST7789_FRAME_RATE_55_HZ  = 0x12,       /**< 55Hz */
    ST7789_FRAME_RATE_53_HZ  = 0x13,       /**< 53Hz */
    ST7789_FRAME_RATE_52_HZ  = 0x14,       /**< 52Hz */
    ST7789_FRAME_RATE_50_HZ  = 0x15,       /**< 50Hz */
    ST7789_FRAME_RATE_49_HZ  = 0x16,       /**< 49Hz */
    ST7789_FRAME_RATE_48_HZ  = 0x17,       /**< 48Hz */
    ST7789_FRAME_RATE_46_HZ  = 0x18,       /**< 46Hz */
    ST7789_FRAME_RATE_45_HZ  = 0x19,       /**< 45Hz */
    ST7789_FRAME_RATE_44_HZ  = 0x1A,       /**< 44Hz */
    ST7789_FRAME_RATE_43_HZ  = 0x1B,       /**< 43Hz */
    ST7789_FRAME_RATE_42_HZ  = 0x1C,       /**< 42Hz */
    ST7789_FRAME_RATE_41_HZ  = 0x1D,       /**< 41Hz */
    ST7789_FRAME_RATE_40_HZ  = 0x1E,       /**< 40Hz */
    ST7789_FRAME_RATE_39_HZ  = 0x1F,       /**< 39Hz */
} st7789_frame_rate_t;

/**
 * @brief st7789 pwm frequency enumeration definition
 */
typedef enum
{
    ST7789_PWM_FREQUENCY_39P2_KHZ   = (0x0 << 3) | (0x0 << 0),        /**< 39.2 KHz */
    ST7789_PWM_FREQUENCY_78P7_KHZ   = (0x1 << 3) | (0x0 << 0),        /**< 78.7 KHz */
    ST7789_PWM_FREQUENCY_158P7_KHZ  = (0x2 << 3) | (0x0 << 0),        /**< 158.7 KHz */
    ST7789_PWM_FREQUENCY_322P6_KHZ  = (0x3 << 3) | (0x0 << 0),        /**< 322.6 KHz */
    ST7789_PWM_FREQUENCY_666P7_KHZ  = (0x4 << 3) | (0x0 << 0),        /**< 666.7 KHz */
    ST7789_PWM_FREQUENCY_1428P6_KHZ = (0x5 << 3) | (0x0 << 0),        /**< 1428.6 KHz */
    ST7789_PWM_FREQUENCY_19P6_KHZ   = (0x0 << 3) | (0x1 << 0),        /**< 19.6 KHz */
    ST7789_PWM_FREQUENCY_39P4_KHZ   = (0x1 << 3) | (0x1 << 0),        /**< 39.4 KHz */
    ST7789_PWM_FREQUENCY_79P4_KHZ   = (0x2 << 3) | (0x1 << 0),        /**< 79.4 KHz */
    ST7789_PWM_FREQUENCY_161P3_KHZ  = (0x3 << 3) | (0x1 << 0),        /**< 161.3 KHz */
    ST7789_PWM_FREQUENCY_333P3_KHZ  = (0x4 << 3) | (0x1 << 0),        /**< 333.3 KHz */
    ST7789_PWM_FREQUENCY_714P3_KHZ  = (0x5 << 3) | (0x1 << 0),        /**< 714.3 KHz */
    ST7789_PWM_FREQUENCY_9P8_KHZ    = (0x0 << 3) | (0x2 << 0),        /**< 9.8 KHz */
    ST7789_PWM_FREQUENCY_19P7_KHZ   = (0x1 << 3) | (0x2 << 0),        /**< 19.7 KHz */
    ST7789_PWM_FREQUENCY_39P7_KHZ   = (0x2 << 3) | (0x2 << 0),        /**< 39.7 KHz */
    ST7789_PWM_FREQUENCY_80P6_KHZ   = (0x3 << 3) | (0x2 << 0),        /**< 80.6 KHz */
    ST7789_PWM_FREQUENCY_166P7_KHZ  = (0x4 << 3) | (0x2 << 0),        /**< 166.7 KHz */
    ST7789_PWM_FREQUENCY_357P1_KHZ  = (0x5 << 3) | (0x2 << 0),        /**< 357.1 KHz */
    ST7789_PWM_FREQUENCY_4P9_KHZ    = (0x0 << 3) | (0x3 << 0),        /**< 4.9 KHz */
    ST7789_PWM_FREQUENCY_9P80_KHZ   = (0x1 << 3) | (0x3 << 0),        /**< 9.80 KHz */
    ST7789_PWM_FREQUENCY_19P8_KHZ   = (0x2 << 3) | (0x3 << 0),        /**< 19.8 KHz */
    ST7789_PWM_FREQUENCY_40P3_KHZ   = (0x3 << 3) | (0x3 << 0),        /**< 40.3 KHz */
    ST7789_PWM_FREQUENCY_83P3_KHZ   = (0x4 << 3) | (0x3 << 0),        /**< 83.3 KHz */
    ST7789_PWM_FREQUENCY_178P6_KHZ  = (0x5 << 3) | (0x3 << 0),        /**< 178.6 KHz */
    ST7789_PWM_FREQUENCY_2P45_KHZ   = (0x0 << 3) | (0x4 << 0),        /**< 2.45 KHz */
    ST7789_PWM_FREQUENCY_4P90_KHZ   = (0x1 << 3) | (0x4 << 0),        /**< 4.90 KHz */
    ST7789_PWM_FREQUENCY_9P9_KHZ    = (0x2 << 3) | (0x4 << 0),        /**< 9.9 KHz */
    ST7789_PWM_FREQUENCY_20P2_KHZ   = (0x3 << 3) | (0x4 << 0),        /**< 20.2 KHz */
    ST7789_PWM_FREQUENCY_41P7_KHZ   = (0x4 << 3) | (0x4 << 0),        /**< 41.7 KHz */
    ST7789_PWM_FREQUENCY_89P3_KHZ   = (0x5 << 3) | (0x4 << 0),        /**< 89.3 KHz */
    ST7789_PWM_FREQUENCY_1P23_KHZ   = (0x0 << 3) | (0x5 << 0),        /**< 1.23 KHz */
    ST7789_PWM_FREQUENCY_2P5_KHZ    = (0x1 << 3) | (0x5 << 0),        /**< 2.5 KHz */
    ST7789_PWM_FREQUENCY_5P0_KHZ    = (0x2 << 3) | (0x5 << 0),        /**< 5.0 KHz */
    ST7789_PWM_FREQUENCY_10P1_KHZ   = (0x3 << 3) | (0x5 << 0),        /**< 10.1 KHz */
    ST7789_PWM_FREQUENCY_20P8_KHZ   = (0x4 << 3) | (0x5 << 0),        /**< 20.8 KHz */
    ST7789_PWM_FREQUENCY_44P6_KHZ   = (0x5 << 3) | (0x5 << 0),        /**< 44.6 KHz */
    ST7789_PWM_FREQUENCY_0P61_KHZ   = (0x0 << 3) | (0x6 << 0),        /**< 0.61 KHz */
    ST7789_PWM_FREQUENCY_1P230_KHZ  = (0x1 << 3) | (0x6 << 0),        /**< 1.230 KHz */
    ST7789_PWM_FREQUENCY_2P48_KHZ   = (0x2 << 3) | (0x6 << 0),        /**< 2.48 KHz */
    ST7789_PWM_FREQUENCY_5P00_KHZ   = (0x3 << 3) | (0x6 << 0),        /**< 5.00 KHz */
    ST7789_PWM_FREQUENCY_10P4_KHZ   = (0x4 << 3) | (0x6 << 0),        /**< 10.4 KHz */
    ST7789_PWM_FREQUENCY_22P3_KHZ   = (0x5 << 3) | (0x6 << 0),        /**< 22.3 KHz */
    ST7789_PWM_FREQUENCY_0P31_KHZ   = (0x0 << 3) | (0x7 << 0),        /**< 0.31 KHz */
    ST7789_PWM_FREQUENCY_0P62_KHZ   = (0x1 << 3) | (0x7 << 0),        /**< 0.62 KHz */
    ST7789_PWM_FREQUENCY_1P24_KHZ   = (0x2 << 3) | (0x7 << 0),        /**< 1.24 KHz */
    ST7789_PWM_FREQUENCY_2P25_KHZ   = (0x3 << 3) | (0x7 << 0),        /**< 2.25 KHz */
    ST7789_PWM_FREQUENCY_5P2_KHZ    = (0x4 << 3) | (0x7 << 0),        /**< 5.2 KHz */
    ST7789_PWM_FREQUENCY_11P2_KHZ   = (0x5 << 3) | (0x7 << 0),        /**< 11.2 KHz */
} st7789_pwm_frequency_t;

/**
 * @brief st7789 avdd enumeration definition
 */
typedef enum
{
    ST7789_AVDD_6P4_V = 0x0,        /**< 6.4V */
    ST7789_AVDD_6P6_V = 0x1,        /**< 6.6V */
    ST7789_AVDD_6P8_V = 0x2,        /**< 6.8V */
} st7789_avdd_t;

/**
 * @brief st7789 avcl enumeration definition
 */
typedef enum
{
    ST7789_AVCL_NEGTIVE_4P4_V = 0x0,        /**< -4.4V */
    ST7789_AVCL_NEGTIVE_4P6_V = 0x1,        /**< -4.6V */
    ST7789_AVCL_NEGTIVE_4P8_V = 0x2,        /**< -4.8V */
    ST7789_AVCL_NEGTIVE_5P0_V = 0x3,        /**< -5.0V */
} st7789_avcl_t;

/**
 * @brief st7789 vds enumeration definition
 */
typedef enum
{
    ST7789_VDS_2P19_V = 0x0,        /**< 2.19V */
    ST7789_VDS_2P3_V  = 0x1,        /**< 2.3V */
    ST7789_VDS_2P4_V  = 0x2,        /**< 2.4V */
    ST7789_VDS_2P51_V = 0x3,        /**< 2.51V */
} st7789_vds_t;

/**
 * @brief st7789 gate scan mode enumeration definition
 */
typedef enum
{
    ST7789_GATE_SCAN_MODE_INTERLACE     = 0x0,        /**< interlace mode */
    ST7789_GATE_SCAN_MODE_NON_INTERLACE = 0x1,        /**< non-interlace mode */
} st7789_gate_scan_mode_t;

/**
 * @brief st7789 gate scan direction enumeration definition
 */
typedef enum
{
    ST7789_GATE_SCAN_DIRECTION_0_319 = 0x0,        /**< 0 - 319 */
    ST7789_GATE_SCAN_DIRECTION_319_0 = 0x1,        /**< 319 - 0 */
} st7789_gate_scan_direction_t;

/**
 * @brief st7789 sbclk div enumeration definition
 */
typedef enum
{
    ST7789_SBCLK_DIV_2 = 0x0,        /**< div2 */
    ST7789_SBCLK_DIV_3 = 0x1,        /**< div3 */
    ST7789_SBCLK_DIV_4 = 0x2,        /**< div4 */
    ST7789_SBCLK_DIV_6 = 0x3,        /**< div6 */
} st7789_sbclk_div_t;

/**
 * @brief st7789 stp14ck div enumeration definition
 */
typedef enum
{
    ST7789_STP14CK_DIV_2 = 0x0,        /**< div2 */
    ST7789_STP14CK_DIV_3 = 0x1,        /**< div3 */
    ST7789_STP14CK_DIV_4 = 0x2,        /**< div4 */
    ST7789_STP14CK_DIV_6 = 0x3,        /**< div6 */
} st7789_stp14ck_div_t;

/**
 * @}
 */

/**
 * @addtogroup st7789_basic_driver
 * @{
 */

/**
 * @brief st7789 handle structure definition
 */
typedef struct st7789_handle_s
{
    uint8_t (*spi_init)(void);                                   /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                 /**< point to a spi_deinit function address */
    uint8_t (*spi_write_cmd)(uint8_t *buf, uint16_t len);        /**< point to a spi_write_cmd function address */
    uint8_t (*cmd_data_gpio_init)(void);                         /**< point to a cmd_data_gpio_init function address */
    uint8_t (*cmd_data_gpio_deinit)(void);                       /**< point to a cmd_data_gpio_deinit function address */
    uint8_t (*cmd_data_gpio_write)(uint8_t value);               /**< point to a cmd_data_gpio_write function address */
    uint8_t (*reset_gpio_init)(void);                            /**< point to a reset_gpio_init function address */
    uint8_t (*reset_gpio_deinit)(void);                          /**< point to a reset_gpio_deinit function address */
    uint8_t (*reset_gpio_write)(uint8_t value);                  /**< point to a reset_gpio_write function address */
    void (*debug_print)(const char *const fmt, ...);             /**< point to a debug_print function address */
    void (*delay_ms)(uint32_t ms);                               /**< point to a delay_ms function address */
    uint8_t inited;                                              /**< inited flag */
    uint16_t column;                                             /**< column */
    uint16_t row;                                                /**< row */
    uint8_t format;                                              /**< format */
    uint8_t buf[ST7789_BUFFER_SIZE + 8];                         /**< inner buffer */
} st7789_handle_t;

/**
 * @brief st7789 information structure definition
 */
typedef struct st7789_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} st7789_info_t;

/**
 * @}
 */

/**
 * @defgroup st7789_link_driver st7789 link driver function
 * @brief    st7789 link driver modules
 * @ingroup  st7789_driver
 * @{
 */

/**
 * @brief     initialize st7789_handle_t structure
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] STRUCTURE is st7789_handle_t
 * @note      none
 */
#define DRIVER_ST7789_LINK_INIT(HANDLE, STRUCTURE)                 memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a spi_init function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_SPI_INIT(HANDLE, FUC)                  (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a spi_deinit function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_SPI_DEINIT(HANDLE, FUC)                (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_write_cmd function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a spi_write_cmd function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_SPI_WRITE_COMMAND(HANDLE, FUC)         (HANDLE)->spi_write_cmd = FUC

/**
 * @brief     link cmd_data_gpio_init function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a cmd_data_gpio_init function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_COMMAND_DATA_GPIO_INIT(HANDLE, FUC)    (HANDLE)->cmd_data_gpio_init = FUC

/**
 * @brief     link cmd_data_gpio_deinit function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a cmd_data_gpio_deinit function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_COMMAND_DATA_GPIO_DEINIT(HANDLE, FUC)  (HANDLE)->cmd_data_gpio_deinit = FUC

/**
 * @brief     link cmd_data_gpio_write function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a cmd_data_gpio_write function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_COMMAND_DATA_GPIO_WRITE(HANDLE, FUC)   (HANDLE)->cmd_data_gpio_write = FUC

/**
 * @brief     link reset_gpio_init function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a reset_gpio_init function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_RESET_GPIO_INIT(HANDLE, FUC)           (HANDLE)->reset_gpio_init = FUC

/**
 * @brief     link reset_gpio_deinit function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a reset_gpio_deinit function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_RESET_GPIO_DEINIT(HANDLE, FUC)         (HANDLE)->reset_gpio_deinit = FUC

/**
 * @brief     link reset_gpio_write function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a reset_gpio_write function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_RESET_GPIO_WRITE(HANDLE, FUC)          (HANDLE)->reset_gpio_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_DELAY_MS(HANDLE, FUC)                  (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an st7789 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_ST7789_LINK_DEBUG_PRINT(HANDLE, FUC)               (HANDLE)->debug_print = FUC

/**
 * @}
 */
 
/**
 * @defgroup st7789_basic_driver st7789 basic driver function
 * @brief    st7789 basic driver modules
 * @ingroup  st7789_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an st7789 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t st7789_info(st7789_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 *            - 5 command && data init failed
 * @note      none
 */
uint8_t st7789_init(st7789_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 *            - 5 reset gpio deinit failed
 *            - 6 command && data deinit failed
 * @note      none
 */
uint8_t st7789_deinit(st7789_handle_t *handle);

/**
 * @brief     set column
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] column is the screen column
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 column > 240
 * @note      none
 */
uint8_t st7789_set_column(st7789_handle_t *handle, uint16_t column);

/**
 * @brief     set row
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] row is the screen row
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 row > 320
 * @note      none
 */
uint8_t st7789_set_row(st7789_handle_t *handle, uint16_t row);

/**
 * @brief     clear the display
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 format is invalid
 * @note      none
 */
uint8_t st7789_clear(st7789_handle_t *handle);

/**
 * @brief     draw a point in the display
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] color is the point color
 * @return    status code
 *            - 0 success
 *            - 1 draw point failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 x is over column
 *            - 5 y is over row
 * @note      x < column && y < row
 */
uint8_t st7789_draw_point(st7789_handle_t *handle, uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief     write a string in the display
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] x is the coordinate x
 * @param[in] y is the coordinate y
 * @param[in] *str points to a write string address
 * @param[in] len is the length of the string
 * @param[in] color is the display color
 * @param[in] font is the string font
 * @return    status code
 *            - 0 success
 *            - 1 draw point failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 x or y is invalid
 * @note      x < column && y < row
 */
uint8_t st7789_write_string(st7789_handle_t *handle, uint16_t x, uint16_t y, char *str, uint16_t len, uint32_t color, st7789_font_t font);

/**
 * @brief     fill the rect
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] color is the display color
 * @return    status code
 *            - 0 success
 *            - 1 fill rect failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 left is over column
 *            - 5 right is over column
 *            - 6 left >= right
 *            - 7 top is over row
 *            - 8 bottom is over row
 *            - 9 top >= bottom
 * @note      left <= column && right <= column && left < right && top <= row && bottom <= row && top < bottom
 */
uint8_t st7789_fill_rect(st7789_handle_t *handle, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint32_t color);

/**
 * @brief     draw a picture
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] *image points to an image buffer
 * @return    status code
 *            - 0 success
 *            - 1 draw picture 12bits failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 left is over column
 *            - 5 right is over column
 *            - 6 left >= right
 *            - 7 top is over row
 *            - 8 bottom is over row
 *            - 9 top >= bottom
 * @note      left <= column && right <= column && left < right && top <= row && bottom <= row && top < bottom
 */
uint8_t st7789_draw_picture_12bits(st7789_handle_t *handle, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t *image);

/**
 * @brief     draw a picture
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] *image points to an image buffer
 * @return    status code
 *            - 0 success
 *            - 1 draw picture 16bits failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 left is over column
 *            - 5 right is over column
 *            - 6 left >= right
 *            - 7 top is over row
 *            - 8 bottom is over row
 *            - 9 top >= bottom
 * @note      left <= column && right <= column && left < right && top <= row && bottom <= row && top < bottom
 */
uint8_t st7789_draw_picture_16bits(st7789_handle_t *handle, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t *image);

/**
 * @brief     draw a picture
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] left is the left coordinate x
 * @param[in] top is the top coordinate y
 * @param[in] right is the right coordinate x
 * @param[in] bottom is the bottom coordinate y
 * @param[in] *image points to an image buffer
 * @return    status code
 *            - 0 success
 *            - 1 draw picture 18bits failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 left is over column
 *            - 5 right is over column
 *            - 6 left >= right
 *            - 7 top is over row
 *            - 8 bottom is over row
 *            - 9 top >= bottom
 * @note      left <= column && right <= column && left < right && top <= row && bottom <= row && top < bottom
 */
uint8_t st7789_draw_picture_18bits(st7789_handle_t *handle, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint32_t *image);

/**
 * @brief     nop
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 nop failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_nop(st7789_handle_t *handle);

/**
 * @brief     software reset
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 software reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_software_reset(st7789_handle_t *handle);

/**
 * @brief     sleep in
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 sleep in failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_sleep_in(st7789_handle_t *handle);

/**
 * @brief     sleep out
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 sleep out failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_sleep_out(st7789_handle_t *handle);

/**
 * @brief     partial display mode on
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 partial display mode on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_partial_display_mode_on(st7789_handle_t *handle);

/**
 * @brief     normal display mode on
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 normal display mode on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_normal_display_mode_on(st7789_handle_t *handle);

/**
 * @brief     display inversion off
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 display inversion off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_display_inversion_off(st7789_handle_t *handle);

/**
 * @brief     display inversion on
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 display inversion on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_display_inversion_on(st7789_handle_t *handle);

/**
 * @brief     set gamma
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] gamma is the set gamma
 * @return    status code
 *            - 0 success
 *            - 1 set gamma failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_gamma(st7789_handle_t *handle, uint8_t gamma);

/**
 * @brief     display off
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 display off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_display_off(st7789_handle_t *handle);

/**
 * @brief     display on
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 display on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_display_on(st7789_handle_t *handle);

/**
 * @brief     set the column address
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] start_address is the start address
 * @param[in] end_address is the end address
 * @return    status code
 *            - 0 success
 *            - 1 set column address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 address is invalid
 *            - 5 start_address >= end_address
 * @note      start_address <= 319 && end_address <= 319 && start_address >= start_address
 */
uint8_t st7789_set_column_address(st7789_handle_t *handle, uint16_t start_address, uint16_t end_address);

/**
 * @brief     set the row address
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] start_address is the start address
 * @param[in] end_address is the end address
 * @return    status code
 *            - 0 success
 *            - 1 set row address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 address is invalid
 *            - 5 start_address >= end_address
 * @note      start_address <= 319 && end_address <= 319 && start_address >= start_address
 */
uint8_t st7789_set_row_address(st7789_handle_t *handle, uint16_t start_address, uint16_t end_address);

/**
 * @brief     memory write
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 memory write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_memory_write(st7789_handle_t *handle, uint8_t *data, uint16_t len);

/**
 * @brief     set partial areas
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] start_row is the start row
 * @param[in] end_row is the end row
 * @return    status code
 *            - 0 success
 *            - 1 set partial areas failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_partial_areas(st7789_handle_t *handle, uint16_t start_row, uint16_t end_row);

/**
 * @brief     set vertical scrolling
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] top_fixed_area is top fixed area line
 * @param[in] scrolling_area is scrolling area line
 * @param[in] bottom_fixed_area is bottom fixed area line
 * @return    status code
 *            - 0 success
 *            - 1 set vertical scrolling failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_vertical_scrolling(st7789_handle_t *handle, uint16_t top_fixed_area,
                                      uint16_t scrolling_area, uint16_t bottom_fixed_area);

/**
 * @brief     tearing effect line off
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 tearing effect line off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_tearing_effect_line_off(st7789_handle_t *handle);

/**
 * @brief     tearing effect line on
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] effect is the tearing effect
 * @return    status code
 *            - 0 success
 *            - 1 tearing effect line on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_tearing_effect_line_on(st7789_handle_t *handle, st7789_tearing_effect_t effect);

/**
 * @brief     set memory data access control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] order is the memory data access control order
 * @return    status code
 *            - 0 success
 *            - 1 set memory data access control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_memory_data_access_control(st7789_handle_t *handle, uint8_t order);

/**
 * @brief     set the vertical scroll start address
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] start_address is the start address
 * @return    status code
 *            - 0 success
 *            - 1 set vertical scroll start address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 address is invalid
 * @note      none
 */
uint8_t st7789_set_vertical_scroll_start_address(st7789_handle_t *handle, uint16_t start_address);

/**
 * @brief     idle mode off
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 idle mode off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_idle_mode_off(st7789_handle_t *handle);

/**
 * @brief     idle mode on
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 idle mode on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_idle_mode_on(st7789_handle_t *handle);

/**
 * @brief     set interface pixel format
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] rgb is the rgb interface color format
 * @param[in] control is control interface color format
 * @return    status code
 *            - 0 success
 *            - 1 set interface pixel format failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_interface_pixel_format(st7789_handle_t *handle, st7789_rgb_interface_color_format_t rgb,
                                          st7789_control_interface_color_format_t control);

/**
 * @brief     memory continue write
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] *data points to a data buffer
 * @param[in] len is the data length
 * @return    status code
 *            - 0 success
 *            - 1 memory continue write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_memory_continue_write(st7789_handle_t *handle, uint8_t *data, uint16_t len);

/**
 * @brief     set tear scanline
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] l is the tear line
 * @return    status code
 *            - 0 success
 *            - 1 set tear scanline failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_tear_scanline(st7789_handle_t *handle, uint16_t l);

/**
 * @brief     set display brightness
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] brightness is the display brightness
 * @return    status code
 *            - 0 success
 *            - 1 set display brightness failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_display_brightness(st7789_handle_t *handle, uint8_t brightness);

/**
 * @brief     set display control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] brightness_control_block is a bool value
 * @param[in] display_dimming is a bool value
 * @param[in] backlight_control is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set display control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_display_control(st7789_handle_t *handle, st7789_bool_t brightness_control_block,
                                   st7789_bool_t display_dimming, st7789_bool_t backlight_control);

/**
 * @brief     set brightness control and color enhancement
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] color_enhancement is a bool value
 * @param[in] mode is the color enhancement mode
 * @param[in] level is the color enhancement level
 * @return    status code
 *            - 0 success
 *            - 1 set brightness control and color enhancement failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_brightness_control_and_color_enhancement(st7789_handle_t *handle, st7789_bool_t color_enhancement,
                                                            st7789_color_enhancement_mode_t mode, st7789_color_enhancement_level_t level);

/**
 * @brief     set cabc minimum brightness
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] brightness is the display brightness
 * @return    status code
 *            - 0 success
 *            - 1 set cabc minimum brightness failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_cabc_minimum_brightness(st7789_handle_t *handle, uint8_t brightness);

/**
 * @}
 */

/**
 * @defgroup st7789_advance_driver st7789 advance driver function
 * @brief    st7789 advance driver modules
 * @ingroup  st7789_driver
 * @{
 */
 
/**
 * @brief     set ram control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] ram_mode is the ram mode
 * @param[in] display_mode is the display mode
 * @param[in] frame_type is the frame type
 * @param[in] data_mode is the data mode
 * @param[in] bus_width is the bus width
 * @param[in] pixel_type is the pixel type
 * @return    status code
 *            - 0 success
 *            - 1 set ram control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_ram_control(st7789_handle_t *handle,
                               st7789_ram_access_t ram_mode,
                               st7789_display_mode_t display_mode,
                               st7789_frame_type_t frame_type,
                               st7789_data_mode_t data_mode,
                               st7789_rgb_bus_width_t bus_width,
                               st7789_pixel_type_t pixel_type);

/**
 * @brief     set rgb interface control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] rgb_mode is the rgb mode
 * @param[in] rgb_if_mode is the rgb if enable mode
 * @param[in] vspl is the vspl active level
 * @param[in] hspl is the hspl active level
 * @param[in] dpl is the dpl active level
 * @param[in] epl is the epl active level
 * @param[in] vbp is the rgb interface vsync back porch setting
 * @param[in] hbp is the rgb interface hsync back porch setting
 * @return    status code
 *            - 0 success
 *            - 1 set rgb interface control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vbp > 0x7F
 *            - 5 hbp > 0x1F
 * @note      0x02 <= vbp <= 0x7F
 *            0x02 <= hbp <= 0x1F
 */
uint8_t st7789_set_rgb_interface_control(st7789_handle_t *handle,
                                         st7789_direct_rgb_mode_t rgb_mode,
                                         st7789_rgb_if_enable_mode_t rgb_if_mode,
                                         st7789_pin_level_t vspl,
                                         st7789_pin_level_t hspl,
                                         st7789_pin_level_t dpl,
                                         st7789_pin_level_t epl,
                                         uint8_t vbp,
                                         uint8_t hbp);

/**
 * @brief     set porch
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] back_porch_normal is the back porch setting in normal mode
 * @param[in] front_porch_normal is the front porch setting in normal mode
 * @param[in] separate_porch_enable is a bool value
 * @param[in] back_porch_idle is the back porch setting in idle mode
 * @param[in] front_porch_idle is the front porch setting in idle mode
 * @param[in] back_porch_partial is the back porch setting in partial mode
 * @param[in] front_porch_partial is the front porch setting in partial mode
 * @return    status code
 *            - 0 success
 *            - 1 set porch failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 back_porch_normal > 0x7F
 *            - 5 front_porch_normal > 0x7F
 *            - 6 back_porch_idle > 0xF
 *            - 7 front_porch_idle > 0xF
 *            - 8 back_porch_partial > 0xF
 *            - 9 front_porch_partial > 0xF
 * @note      0x01 <= back_porch_normal <= 0x7F
 *            0x01 <= front_porch_normal <= 0x7F
 *            0x01 <= back_porch_idle <= 0xF
 *            0x01 <= front_porch_idle <= 0xF
 *            0x01 <= back_porch_partial <= 0xF
 *            0x01 <= front_porch_partial <= 0xF
 */
uint8_t st7789_set_porch(st7789_handle_t *handle,
                         uint8_t back_porch_normal,
                         uint8_t front_porch_normal,
                         st7789_bool_t separate_porch_enable,
                         uint8_t back_porch_idle,
                         uint8_t front_porch_idle, 
                         uint8_t back_porch_partial,
                         uint8_t front_porch_partial);

/**
 * @brief     set frame rate control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] separate_fr_control is a bool value
 * @param[in] div_control is the frame rate divided control
 * @param[in] idle_mode is the inversion idle mode
 * @param[in] idle_frame_rate is the idle frame rate
 * @param[in] partial_mode is the inversion partial mode
 * @param[in] partial_frame_rate is the partial frame rate
 * @return    status code
 *            - 0 success
 *            - 1 set frame rate control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 idle_frame_rate > 0x1F
 *            - 5 partial_frame_rate > 0x1F
 * @note      0 <= idle_frame_rate <= 0x1F
 *            0 <= partial_frame_rate <= 0x1F
 */
uint8_t st7789_set_frame_rate_control(st7789_handle_t *handle,
                                      st7789_bool_t separate_fr_control,
                                      st7789_frame_rate_divided_control_t div_control,
                                      st7789_inversion_idle_mode_t idle_mode,
                                      uint8_t idle_frame_rate,
                                      st7789_inversion_partial_mode_t partial_mode,
                                      uint8_t partial_frame_rate);

/**
 * @brief     set partial mode control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] level is the non-display source output level
 * @param[in] mode is the non-display area scan mode
 * @param[in] frequency is the non-display frame frequency
 * @return    status code
 *            - 0 success
 *            - 1 set partial mode control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_partial_mode_control(st7789_handle_t *handle,
                                        st7789_non_display_source_output_level_t level,
                                        st7789_non_display_area_scan_mode_t mode,
                                        st7789_non_display_frame_frequency_t frequency);

/**
 * @brief     set gate control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] vghs is the vghs level
 * @param[in] vgls is the vgls level
 * @return    status code
 *            - 0 success
 *            - 1 set gate control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_gate_control(st7789_handle_t *handle, st7789_vghs_t vghs, st7789_vgls_t vgls);

/**
 * @brief     set gate on timing adjustment
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] gate_on_timing_adjustment is the gate on timing adjustment
 * @param[in] gate_off_timing_adjustment_rgb is the gate off timing adjustment in rgb interface
 * @param[in] gate_off_timing_adjustment is the gate off timing adjustment
 * @return    status code
 *            - 0 success
 *            - 1 set gate on timing adjustment failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      gate_on_timing_adjustment <= 0x3F
 *            gate_off_timing_adjustment_rgb <= 0xF
 *            gate_off_timing_adjustment <= 0xF
 */
uint8_t st7789_set_gate_on_timing_adjustment(st7789_handle_t *handle,
                                             uint8_t gate_on_timing_adjustment,
                                             uint8_t gate_off_timing_adjustment_rgb,
                                             uint8_t gate_off_timing_adjustment);

/**
 * @brief     enable or disable digital gamma
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set digital gamma failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_digital_gamma(st7789_handle_t *handle, st7789_bool_t enable);

/**
 * @brief     set vcoms
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] vcoms is the vcoms
 * @return    status code
 *            - 0 success
 *            - 1 set vcoms failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vcoms > 0x3F
 * @note      0 <= vcoms <= 0x3F
 */
uint8_t st7789_set_vcoms(st7789_handle_t *handle, uint8_t vcoms);

/**
 * @brief      convert the vcom to the register raw data
 * @param[in]  *handle points to an st7789 handle structure
 * @param[in]  v is the vcom
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vcom_convert_to_register(st7789_handle_t *handle, float v, uint8_t *reg);

/**
 * @brief      convert the register raw data to the vcom
 * @param[in]  *handle points to an st7789 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *v points to a vcom buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vcom_convert_to_data(st7789_handle_t *handle, uint8_t reg, float *v);

/**
 * @brief     set lcm control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] xmy is a bool value
 * @param[in] xbgr is a bool value
 * @param[in] xinv is a bool value
 * @param[in] xmx is a bool value
 * @param[in] xmh is a bool value
 * @param[in] xmv is a bool value
 * @param[in] xgs is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set lcm control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_lcm_control(st7789_handle_t *handle,
                               st7789_bool_t xmy,
                               st7789_bool_t xbgr,
                               st7789_bool_t xinv,
                               st7789_bool_t xmx,
                               st7789_bool_t xmh,
                               st7789_bool_t xmv,
                               st7789_bool_t xgs);

/**
 * @brief     set id code setting
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] *id points to an id buffer
 * @return    status code
 *            - 0 success
 *            - 1 set id code setting failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_id_code_setting(st7789_handle_t *handle, uint8_t id[3]);

/**
 * @brief     set vdv vrh from
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] from is the vdv and vrh from
 * @return    status code
 *            - 0 success
 *            - 1 set vdv vrh from failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_vdv_vrh_from(st7789_handle_t *handle, st7789_vdv_vrh_from_t from);

/**
 * @brief     set vrhs
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] vrhs is the set vrhs
 * @return    status code
 *            - 0 success
 *            - 1 set vrhs failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vrhs > 0x27
 * @note      0 <= vrhs <= 0x27
 */
uint8_t st7789_set_vrhs(st7789_handle_t *handle, uint8_t vrhs);

/**
 * @brief      convert the vrhs to the register raw data
 * @param[in]  *handle points to an st7789 handle structure
 * @param[in]  v is the vcom
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vrhs_convert_to_register(st7789_handle_t *handle, float v, uint8_t *reg);

/**
 * @brief      convert the register raw data to the vrhs
 * @param[in]  *handle points to an st7789 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *v points to a vcom buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vrhs_convert_to_data(st7789_handle_t *handle, uint8_t reg, float *v);

/**
 * @brief     set vdv
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] vdv is the set vdv
 * @return    status code
 *            - 0 success
 *            - 1 set vdv failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vdv > 0x3F
 * @note      0 <= vdv <= 0x3F
 */
uint8_t st7789_set_vdv(st7789_handle_t *handle, uint8_t vdv);

/**
 * @brief      convert the vdv to the register raw data
 * @param[in]  *handle points to an st7789 handle structure
 * @param[in]  v is the vcom
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vdv_convert_to_register(st7789_handle_t *handle, float v, uint8_t *reg);

/**
 * @brief      convert the register raw data to the vdv
 * @param[in]  *handle points to an st7789 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *v points to a vcom buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vdv_convert_to_data(st7789_handle_t *handle, uint8_t reg, float *v);

/**
 * @brief     set vcoms offset
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] offset is the vcoms offset
 * @return    status code
 *            - 0 success
 *            - 1 set vcoms offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 offset > 0x3F
 * @note      0 <= offset <= 0x3F
 */
uint8_t st7789_set_vcoms_offset(st7789_handle_t *handle, uint8_t offset);

/**
 * @brief      convert the vcoms offset to the register raw data
 * @param[in]  *handle points to an st7789 handle structure
 * @param[in]  v is the vcoms offset
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vcoms_offset_convert_to_register(st7789_handle_t *handle, float v, uint8_t *reg);

/**
 * @brief      convert the register raw data to the vcoms offset
 * @param[in]  *handle points to an st7789 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *v points to a vcoms offset buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vcoms_offset_convert_to_data(st7789_handle_t *handle, uint8_t reg, float *v);

/**
 * @brief     set frame rate
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] selection is the inversion selection
 * @param[in] rate is the frame rate
 * @return    status code
 *            - 0 success
 *            - 1 set frame rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_frame_rate(st7789_handle_t *handle, st7789_inversion_selection_t selection, st7789_frame_rate_t rate);

/**
 * @brief     set cabc control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] led_on is a bool value
 * @param[in] led_pwm_init is a bool value
 * @param[in] led_pwm_fix is a bool value
 * @param[in] led_pwm_polarity is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set cabc control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_cabc_control(st7789_handle_t *handle,
                                st7789_bool_t led_on,
                                st7789_bool_t led_pwm_init,
                                st7789_bool_t led_pwm_fix,
                                st7789_bool_t led_pwm_polarity);

/**
 * @brief     set pwm frequency
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] frequency is the pwm frequency
 * @return    status code
 *            - 0 success
 *            - 1 set pwm frequency failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_pwm_frequency(st7789_handle_t *handle, st7789_pwm_frequency_t frequency);

/**
 * @brief     set power control 1
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] avdd is the avdd param
 * @param[in] avcl is the avcl param
 * @param[in] vds is the vds param
 * @return    status code
 *            - 0 success
 *            - 1 set power control 1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_power_control_1(st7789_handle_t *handle, st7789_avdd_t avdd, st7789_avcl_t avcl, st7789_vds_t vds);

/**
 * @brief     enable vap van signal output
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 enable vap van signal output failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_enable_vap_van_signal_output(st7789_handle_t *handle);

/**
 * @brief     enable or disable command 2
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set command 2 enable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_command_2_enable(st7789_handle_t *handle, st7789_bool_t enable);

/**
 * @brief     set positive voltage gamma control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] *param points to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 set positive voltage gamma control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_positive_voltage_gamma_control(st7789_handle_t *handle, uint8_t param[14]);

/**
 * @brief     set negative voltage gamma control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] *param points to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 set negative voltage gamma control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_negative_voltage_gamma_control(st7789_handle_t *handle, uint8_t param[14]);

/**
 * @brief     set red digital gamma look up table
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] *param points to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 set digital gamma look up table red failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_digital_gamma_look_up_table_red(st7789_handle_t *handle, uint8_t param[64]);

/**
 * @brief     set blue digital gamma look up table
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] *param points to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 set digital gamma look up table blue failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_digital_gamma_look_up_table_blue(st7789_handle_t *handle, uint8_t param[64]);

/**
 * @brief     set gate
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] gate_line_number is the gate line number
 * @param[in] first_scan_line_number is the first scan line number
 * @param[in] mode is the gate scan mode
 * @param[in] direction is the gate scan direction
 * @return    status code
 *            - 0 success
 *            - 1 set gate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 gate_line_number > 0x3F
 *            - 5 first_scan_line_number > 0x3F
 * @note      0 <= gate_line_number <= 0x3F
 *            0 <= first_scan_line_number 0x3F
 */
uint8_t st7789_set_gate(st7789_handle_t *handle,
                        uint8_t gate_line_number,
                        uint8_t first_scan_line_number,
                        st7789_gate_scan_mode_t mode,
                        st7789_gate_scan_direction_t direction);

/**
 * @brief      convert the gate line to the register raw data
 * @param[in]  *handle points to an st7789 handle structure
 * @param[in]  l is the gate line
 * @param[out] *reg points to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_gate_line_convert_to_register(st7789_handle_t *handle, uint16_t l, uint8_t *reg);

/**
 * @brief      convert the register raw data to the gate line
 * @param[in]  *handle points to an st7789 handle structure
 * @param[in]  reg is the register raw data
 * @param[out] *l points to a gate line buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_gate_line_convert_to_data(st7789_handle_t *handle, uint8_t reg, uint16_t *l);

/**
 * @brief     set spi2 enable
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] date_lane is a bool value
 * @param[in] command_table_2 is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set spi2 enable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_spi2_enable(st7789_handle_t *handle, st7789_bool_t date_lane, st7789_bool_t command_table_2);

/**
 * @brief     set power control 2
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] sbclk is the sbclk div
 * @param[in] stp14ck is the stp14ck div
 * @return    status code
 *            - 0 success
 *            - 1 set power control 2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_power_control_2(st7789_handle_t *handle, st7789_sbclk_div_t sbclk, st7789_stp14ck_div_t stp14ck);

/**
 * @brief     set equalize time control
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] source_equalize_time is the source equalize time
 * @param[in] source_pre_drive_time is the source pre drive time
 * @param[in] gate_equalize_time is the gate equalize time
 * @return    status code
 *            - 0 success
 *            - 1 set equalize time control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 source_equalize_time > 0x1F
 *            - 5 source_pre_drive_time > 0x1F
 *            - 6 gate_equalize_time > 0xF
 * @note      0 <= source_equalize_time <= 0x1F
 */
uint8_t st7789_set_equalize_time_control(st7789_handle_t *handle,
                                         uint8_t source_equalize_time,
                                         uint8_t source_pre_drive_time,
                                         uint8_t gate_equalize_time);

/**
 * @brief     set program mode control
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set program mode control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_program_mode_control(st7789_handle_t *handle);

/**
 * @brief     enable or disable program mode
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set program mode enable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_program_mode_enable(st7789_handle_t *handle, st7789_bool_t enable);

/**
 * @brief     set nvm setting
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] addr is the nvm address
 * @param[in] data is the nvm set data
 * @return    status code
 *            - 0 success
 *            - 1 set nvm setting failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_nvm_setting(st7789_handle_t *handle, uint8_t addr, uint8_t data);

/**
 * @brief     set program action
 * @param[in] *handle points to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set program action failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_program_action(st7789_handle_t *handle);

/**
 * @}
 */

/**
 * @defgroup st7789_extend_driver st7789 extend driver function
 * @brief    st7789 extend driver modules
 * @ingroup  st7789_driver
 * @{
 */

/**
 * @brief     write the command
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] cmd is the send command
 * @return    status code
 *            - 0 success
 *            - 1 write command failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_write_cmd(st7789_handle_t *handle, uint8_t cmd);

/**
 * @brief     write the data
 * @param[in] *handle points to an st7789 handle structure
 * @param[in] data is the send data
 * @return    status code
 *            - 0 success
 *            - 1 write data failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_write_data(st7789_handle_t *handle, uint8_t data);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
