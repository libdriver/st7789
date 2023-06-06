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
 * @file      driver_st7789_display_test.c
 * @brief     driver st7789 display test source file
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

#include "driver_st7789_display_test.h"
#include "driver_st7789_display_image.h"
#include <stdlib.h>

static st7789_handle_t gs_handle;        /**< st7789 handle */

/**
 * @brief  display test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t st7789_display_test(void)
{
    uint8_t res;
    uint8_t reg;
    uint16_t i;
    uint16_t j;
    uint8_t param[14];
    uint8_t params[64];
    st7789_info_t info;
    char test_str1[] ="Test";
    char test_str2[] ="st7789";
    char test_str3[] ="ABCabc";
    char test_str4[] ="123?!#$%";
    
    /* link functions */
    DRIVER_ST7789_LINK_INIT(&gs_handle, st7789_handle_t);
    DRIVER_ST7789_LINK_SPI_INIT(&gs_handle, st7789_interface_spi_init);
    DRIVER_ST7789_LINK_SPI_DEINIT(&gs_handle, st7789_interface_spi_deinit);
    DRIVER_ST7789_LINK_SPI_WRITE_COMMAND(&gs_handle, st7789_interface_spi_write_cmd);
    DRIVER_ST7789_LINK_COMMAND_DATA_GPIO_INIT(&gs_handle, st7789_interface_cmd_data_gpio_init);
    DRIVER_ST7789_LINK_COMMAND_DATA_GPIO_DEINIT(&gs_handle, st7789_interface_cmd_data_gpio_deinit);
    DRIVER_ST7789_LINK_COMMAND_DATA_GPIO_WRITE(&gs_handle, st7789_interface_cmd_data_gpio_write);
    DRIVER_ST7789_LINK_RESET_GPIO_INIT(&gs_handle, st7789_interface_reset_gpio_init);
    DRIVER_ST7789_LINK_RESET_GPIO_DEINIT(&gs_handle, st7789_interface_reset_gpio_deinit);
    DRIVER_ST7789_LINK_RESET_GPIO_WRITE(&gs_handle, st7789_interface_reset_gpio_write);
    DRIVER_ST7789_LINK_DELAY_MS(&gs_handle, st7789_interface_delay_ms);
    DRIVER_ST7789_LINK_DEBUG_PRINT(&gs_handle, st7789_interface_debug_print);
    
    /* st7789 info */
    res = st7789_info(&info);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        st7789_interface_debug_print("st7789: chip is %s.\n", info.chip_name);
        st7789_interface_debug_print("st7789: manufacturer is %s.\n", info.manufacturer_name);
        st7789_interface_debug_print("st7789: interface is %s.\n", info.interface);
        st7789_interface_debug_print("st7789: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        st7789_interface_debug_print("st7789: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        st7789_interface_debug_print("st7789: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        st7789_interface_debug_print("st7789: max current is %0.2fmA.\n", info.max_current_ma);
        st7789_interface_debug_print("st7789: max temperature is %0.1fC.\n", info.temperature_max);
        st7789_interface_debug_print("st7789: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start display test */
    st7789_interface_debug_print("st7789: start display test.\n");
    
    /* st7789 init */
    res = st7789_init(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: init failed.\n");
        
        return 1;
    }
    
    /* set column */
    res = st7789_set_column(&gs_handle, 240);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set column failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set row */
    res = st7789_set_row(&gs_handle, 320);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set row failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* sleep out */
    res = st7789_sleep_out(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: sleep out failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* idle mode off */
    res = st7789_idle_mode_off(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: idle mode off failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* normal display mode on */
    res = st7789_normal_display_mode_on(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: normal display mode on failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* display inversion on */
    res = st7789_display_inversion_on(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: display inversion on failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gamma */
    res = st7789_set_gamma(&gs_handle, ST7789_GAMMA_CURVE_1);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set gamma failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set memory data access control */
    res = st7789_set_memory_data_access_control(&gs_handle, ST7789_ORDER_PAGE_TOP_TO_BOTTOM | ST7789_ORDER_COLUMN_LEFT_TO_RIGHT | 
                                                            ST7789_ORDER_PAGE_COLUMN_NORMAL | ST7789_ORDER_LINE_TOP_TO_BOTTOM |
                                                            ST7789_ORDER_COLOR_RGB | ST7789_ORDER_REFRESH_LEFT_TO_RIGHT);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set memory data access control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* 262k 16bit */
    res = st7789_set_interface_pixel_format(&gs_handle, ST7789_RGB_INTERFACE_COLOR_FORMAT_262K, ST7789_CONTROL_INTERFACE_COLOR_FORMAT_16_BIT);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set interface pixel format failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* max brightness */
    res = st7789_set_display_brightness(&gs_handle, 0xFF);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set display brightness failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable brightness control */
    res = st7789_set_display_control(&gs_handle, ST7789_BOOL_FALSE, ST7789_BOOL_FALSE, ST7789_BOOL_FALSE);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set display control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable color enhancement */
    res = st7789_set_brightness_control_and_color_enhancement(&gs_handle, ST7789_BOOL_TRUE,
                                                              ST7789_COLOR_ENHANCEMENT_MODE_USER_INTERFACE, ST7789_COLOR_ENHANCEMENT_LEVEL_HIGH);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set brightness control and color enhancement failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set 0x00 */
    res = st7789_set_cabc_minimum_brightness(&gs_handle, 0x00);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set cabc minimum brightness failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    } 
    
    /* set ram control */
    res = st7789_set_ram_control(&gs_handle,
                                 ST7789_RAM_ACCESS_MCU,
                                 ST7789_DISPLAY_MODE_MCU,
                                 ST7789_FRAME_TYPE_0,
                                 ST7789_DATA_MODE_MSB,
                                 ST7789_RGB_BUS_WIDTH_18_BIT,
                                 ST7789_PIXEL_TYPE_0);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set ram control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    } 
    
    /* set rgb interface control */
    res = st7789_set_rgb_interface_control(&gs_handle,
                                           ST7789_DIRECT_RGB_MODE_MEM,
                                           ST7789_RGB_IF_ENABLE_MODE_MCU,
                                           ST7789_PIN_LEVEL_LOW,
                                           ST7789_PIN_LEVEL_LOW,
                                           ST7789_PIN_LEVEL_LOW,
                                           ST7789_PIN_LEVEL_LOW,
                                           0x02,
                                           0x14);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set rgb interface control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set porch */
    res = st7789_set_porch(&gs_handle,
                           0x0C,
                           0x0C,
                           ST7789_BOOL_FALSE,
                           0x03,
                           0x03, 
                           0x03,
                           0x03);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set porch failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set frame rate control */
    res = st7789_set_frame_rate_control(&gs_handle,
                                        ST7789_BOOL_FALSE,
                                        ST7789_FRAME_RATE_DIVIDED_CONTROL_DIV_1,
                                        ST7789_INVERSION_IDLE_MODE_DOT, 
                                        0x0F,
                                        ST7789_INVERSION_PARTIAL_MODE_DOT,
                                        0x0F);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set frame rate control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set partial mode control */
    res = st7789_set_partial_mode_control(&gs_handle,
                                          ST7789_NON_DISPLAY_SOURCE_OUTPUT_LEVEL_V63,
                                          ST7789_NON_DISPLAY_AREA_SCAN_MODE_NORMAL,
                                          ST7789_NON_DISPLAY_FRAME_FREQUENCY_EVERY);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set partial mode control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gate control */
    res = st7789_set_gate_control(&gs_handle, ST7789_VGHS_14P97_V, ST7789_VGLS_NEGATIVE_8P23);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set gate control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gate on timing adjustment */
    res = st7789_set_gate_on_timing_adjustment(&gs_handle, 
                                               0x22,
                                               0x07,
                                               0x05);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set gate on timing adjustment failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable digital gamma */
    res = st7789_set_digital_gamma(&gs_handle, ST7789_BOOL_TRUE);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set digital gamma failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* vcom convert to register  */
    res = st7789_vcom_convert_to_register(&gs_handle, 1.625f, &reg);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: vcom convert to register failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set vcoms */
    res = st7789_set_vcoms(&gs_handle, reg);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set vcoms failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set lcm control */
    res = st7789_set_lcm_control(&gs_handle,
                                 ST7789_BOOL_FALSE,
                                 ST7789_BOOL_TRUE,
                                 ST7789_BOOL_FALSE,
                                 ST7789_BOOL_TRUE,
                                 ST7789_BOOL_TRUE,
                                 ST7789_BOOL_FALSE,
                                 ST7789_BOOL_FALSE);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set lcm control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* from cmd */
    res = st7789_set_vdv_vrh_from(&gs_handle, ST7789_VDV_VRH_FROM_CMD);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set vdv vrh from failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* vrhs convert to register */
    res = st7789_vrhs_convert_to_register(&gs_handle, 4.8f, &reg);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: vrhs convert to register failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set vrhs */
    res = st7789_set_vrhs(&gs_handle, reg);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set vrhs failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* vdv convert to register */
    res = st7789_vdv_convert_to_register(&gs_handle, 0.0f, &reg);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: vdv convert to register failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set vdv */
    res = st7789_set_vdv(&gs_handle, reg);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set vdv failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* vcoms offset convert to register */
    res = st7789_vcoms_offset_convert_to_register(&gs_handle, 0.0f, &reg);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: vcoms offset convert to register failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set vcoms offset */
    res = st7789_set_vcoms_offset(&gs_handle, reg);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set vcoms offset failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set frame rate */
    res = st7789_set_frame_rate(&gs_handle, ST7789_INVERSION_SELECTION_DOT, ST7789_FRAME_RATE_60_HZ);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set frame rate failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set cabc control */
    res = st7789_set_cabc_control(&gs_handle,
                                  ST7789_BOOL_FALSE,
                                  ST7789_BOOL_FALSE,
                                  ST7789_BOOL_FALSE,
                                  ST7789_BOOL_FALSE);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set cabc control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set pwm frequency */
    res = st7789_set_pwm_frequency(&gs_handle, ST7789_PWM_FREQUENCY_9P8_KHZ);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set pwm frequency failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set power control 1 */
    res = st7789_set_power_control_1(&gs_handle, ST7789_AVDD_6P8_V, ST7789_AVCL_NEGTIVE_4P8_V, ST7789_VDS_2P3_V);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set power control 1 failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set command 2 disable */
    res = st7789_set_command_2_enable(&gs_handle, ST7789_BOOL_FALSE);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set command 2 enable failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set positive voltage gamma control */
    param[0] = 0xD0;
    param[1] = 0x04;
    param[2] = 0x0D;
    param[3] = 0x11;
    param[4] = 0x13;
    param[5] = 0x2B;
    param[6] = 0x3F;
    param[7] = 0x54;
    param[8] = 0x4C;
    param[9] = 0x18;
    param[10] = 0x0D;
    param[11] = 0x0B;
    param[12] = 0x1F;
    param[13] = 0x23;
    res = st7789_set_positive_voltage_gamma_control(&gs_handle, param);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set positive voltage gamma control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set negative voltage gamma control */
    param[0] = 0xD0;
    param[1] = 0x04;
    param[2] = 0x0C;
    param[3] = 0x11;
    param[4] = 0x13;
    param[5] = 0x2C;
    param[6] = 0x3F;
    param[7] = 0x44;
    param[8] = 0x51;
    param[9] = 0x2F;
    param[10] = 0x1F;
    param[11] = 0x1F;
    param[12] = 0x20;
    param[13] = 0x23;
    res = st7789_set_negative_voltage_gamma_control(&gs_handle, param);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set negative voltage gamma control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* create the table */
    for (i = 0; i < 64; i++)
    {
        params[i] = i * 4;
    }
    
    /* set digital gamma look up table red */
    res = st7789_set_digital_gamma_look_up_table_red(&gs_handle, params);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set digital gamma look up table red ailed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set digital gamma look up table blue */
    res = st7789_set_digital_gamma_look_up_table_blue(&gs_handle, params);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set digital gamma look up table blue ailed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* gate line convert to register */
    res = st7789_gate_line_convert_to_register(&gs_handle, 320, &reg);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: gate line convert to register failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gate */
    res = st7789_set_gate(&gs_handle,
                          reg,
                          0x00,
                          ST7789_GATE_SCAN_MODE_INTERLACE,
                          ST7789_GATE_SCAN_DIRECTION_0_319);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set gate failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable spi2 */
    res = st7789_set_spi2_enable(&gs_handle, ST7789_BOOL_FALSE, ST7789_BOOL_FALSE);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set spi2 enable failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set power control 2 */
    res = st7789_set_power_control_2(&gs_handle, ST7789_SBCLK_DIV_3, ST7789_STP14CK_DIV_6);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set power control 2 failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set equalize time control */
    res = st7789_set_equalize_time_control(&gs_handle, 0x11, 0x11, 0x08);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set equalize time control failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable program mode */
    res = st7789_set_program_mode_enable(&gs_handle, ST7789_BOOL_FALSE);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: set program mode enable ailed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* display on */
    res = st7789_display_on(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: display on failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* clear */
    res = st7789_clear(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: clear failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* font 12 test */
    st7789_interface_debug_print("st7789: font 12 test.\n");
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 0, test_str1, (uint16_t)strlen(test_str1), 0xF800U, ST7789_FONT_12);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 50, test_str2, (uint16_t)strlen(test_str2), 0x07E0U, ST7789_FONT_12);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 100, test_str3, (uint16_t)strlen(test_str3), 0x003FU, ST7789_FONT_12);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 150, test_str4, (uint16_t)strlen(test_str4), 0xFFFFU, ST7789_FONT_12);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 1000ms */
    st7789_interface_delay_ms(1000);
    
    /* clear */
    res = st7789_clear(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: clear failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* font 16 test */
    st7789_interface_debug_print("st7789: font 16 test.\n");
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 0, test_str1, (uint16_t)strlen(test_str1), 0xF800U, ST7789_FONT_16);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 50, test_str2, (uint16_t)strlen(test_str2), 0x07E0U, ST7789_FONT_16);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 100, test_str3, (uint16_t)strlen(test_str3), 0x003FU, ST7789_FONT_16);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 150, test_str4, (uint16_t)strlen(test_str4), 0xFFFFU, ST7789_FONT_16);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 1000ms */
    st7789_interface_delay_ms(1000);
    
    /* clear */
    res = st7789_clear(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: clear failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* font 24 test */
    st7789_interface_debug_print("st7789: font 24 test.\n");
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 0, test_str1, (uint16_t)strlen(test_str1), 0xF800U, ST7789_FONT_24);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 50, test_str2, (uint16_t)strlen(test_str2), 0x07E0U, ST7789_FONT_24);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 100, test_str3, (uint16_t)strlen(test_str3), 0x003FU, ST7789_FONT_24);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* write string */
    res = st7789_write_string(&gs_handle, 0, 150, test_str4, (uint16_t)strlen(test_str4), 0xFFFFU, ST7789_FONT_24);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: write string failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 1000ms */
    st7789_interface_delay_ms(1000);
    
    /* clear */
    res = st7789_clear(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: clear failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* rectangle test */
    st7789_interface_debug_print("st7789: rectangle test.\n");
    
    /* fill rect */
    res = st7789_fill_rect(&gs_handle, 0, 0, 100, 100, 0xF800U);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: fill rect failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* fill rect */
    res = st7789_fill_rect(&gs_handle, 0, 150, 100, 200, 0x003FU);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: fill rect failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* fill rect */
    res = st7789_fill_rect(&gs_handle, 0, 280, 200,310, 0x08E0U);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: fill rect failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 1000ms */
    st7789_interface_delay_ms(1000);
    
    /* clear */
    res = st7789_clear(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: clear failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* rand point test */
    st7789_interface_debug_print("st7789: rand point test.\n");
    
    for (i = 0; i < 240; i++)
    {
        for (j = 0; j < 320; j++)
        {
            if ((rand() % 2) != 0)
            {
                res = st7789_draw_point(&gs_handle, i, j, 0xFFFFU);
                if (res != 0)
                {
                    st7789_interface_debug_print("st7789: draw point failed.\n");
                    (void)st7789_deinit(&gs_handle);
                    
                    return 1;
                }
            }
        }
    }
    
    /* delay 1000ms */
    st7789_interface_delay_ms(1000);
    
    /* clear */
    res = st7789_clear(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: clear failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* picture test */
    st7789_interface_debug_print("st7789: picture test.\n");
    
    /* draw picture */
    res = st7789_draw_picture_16bits(&gs_handle, 0, 0, 239, 319, (uint16_t *)gsc_image);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: draw picture 16bits failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 1000ms */
    st7789_interface_delay_ms(1000);
    
    /* clear */
    res = st7789_clear(&gs_handle);
    if (res != 0)
    {
        st7789_interface_debug_print("st7789: clear failed.\n");
        (void)st7789_deinit(&gs_handle);
        
        return 1;
    }
    
    /* finish display test */
    st7789_interface_debug_print("st7789: finish display test.\n");
    (void)st7789_deinit(&gs_handle);
    
    return 0;
}
