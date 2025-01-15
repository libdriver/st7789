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
 * @file      driver_st7789.c
 * @brief     driver st7789 source file
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

#include "driver_st7789.h"
#include "driver_st7789_font.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Sitronix ST7789"        /**< chip name */
#define MANUFACTURER_NAME         "Sitronix"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.4f                     /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.3f                     /**< chip max supply voltage */
#define MAX_CURRENT               7.5f                     /**< chip max current */
#define TEMPERATURE_MIN           -30.0f                   /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                    /**< chip max operating temperature */
#define DRIVER_VERSION            1000                     /**< driver version */

/**
 * @brief command data type definition
 */
#define ST7789_CMD         0        /**< command type */
#define ST7789_DATA        1        /**< data type */

/**
 * @brief chip command definition
 */
#define ST7789_CMD_NOP             0x00        /**< no operation command */
#define ST7789_CMD_SWRESET         0x01        /**< software reset command */
#define ST7789_CMD_SLPIN           0x10        /**< sleep in command */
#define ST7789_CMD_SLPOUT          0x11        /**< sleep out command */
#define ST7789_CMD_PTLON           0x12        /**< partial mode on command */
#define ST7789_CMD_NORON           0x13        /**< normal display mode on command */
#define ST7789_CMD_INVOFF          0x20        /**< display inversion off command */
#define ST7789_CMD_INVON           0x21        /**< display inversion on command */
#define ST7789_CMD_GAMSET          0x26        /**< display inversion set command */
#define ST7789_CMD_DISPOFF         0x28        /**< display off command */
#define ST7789_CMD_DISPON          0x29        /**< display on command */
#define ST7789_CMD_CASET           0x2A        /**< column address set command */
#define ST7789_CMD_RASET           0x2B        /**< row address set command */
#define ST7789_CMD_RAMWR           0x2C        /**< memory write command */
#define ST7789_CMD_PTLAR           0x30        /**< partial start/end address set command */
#define ST7789_CMD_VSCRDEF         0x33        /**< vertical scrolling definition command */
#define ST7789_CMD_TEOFF           0x34        /**< tearing effect line off command */
#define ST7789_CMD_TEON            0x35        /**< tearing effect line on command */
#define ST7789_CMD_MADCTL          0x36        /**< memory data access control command */
#define ST7789_CMD_VSCRSADD        0x37        /**< vertical scrolling start address command */
#define ST7789_CMD_IDMOFF          0x38        /**< idle mode off command */
#define ST7789_CMD_IDMON           0x39        /**< idle mode on command */
#define ST7789_CMD_COLMOD          0x3A        /**< interface pixel format command */
#define ST7789_CMD_RAMWRC          0x3C        /**< memory write continue command */
#define ST7789_CMD_TESCAN          0x44        /**< set tear scanline command */
#define ST7789_CMD_WRDISBV         0x51        /**< write display brightness command */
#define ST7789_CMD_WRCTRLD         0x53        /**< write CTRL display command */
#define ST7789_CMD_WRCACE          0x55        /**< write content adaptive brightness control and color enhancement command */
#define ST7789_CMD_WRCABCMB        0x5E        /**< write CABC minimum brightness command */
#define ST7789_CMD_RAMCTRL         0xB0        /**< ram control command */
#define ST7789_CMD_RGBCTRL         0xB1        /**< rgb control command */
#define ST7789_CMD_PORCTRL         0xB2        /**< porch control command */
#define ST7789_CMD_FRCTRL1         0xB3        /**< frame rate control 1 command */
#define ST7789_CMD_PARCTRL         0xB5        /**< partial mode control command */
#define ST7789_CMD_GCTRL           0xB7        /**< gate control command */
#define ST7789_CMD_GTADJ           0xB8        /**< gate on timing adjustment command */
#define ST7789_CMD_DGMEN           0xBA        /**< digital gamma enable command */
#define ST7789_CMD_VCOMS           0xBB        /**< vcoms setting command */
#define ST7789_CMD_LCMCTRL         0xC0        /**< lcm control command */
#define ST7789_CMD_IDSET           0xC1        /**< id setting command */
#define ST7789_CMD_VDVVRHEN        0xC2        /**< vdv and vrh command enable command */
#define ST7789_CMD_VRHS            0xC3        /**< vrh set command */
#define ST7789_CMD_VDVSET          0xC4        /**< vdv setting command */
#define ST7789_CMD_VCMOFSET        0xC5        /**< vcoms offset set command */
#define ST7789_CMD_FRCTR2          0xC6        /**< fr control 2 command */
#define ST7789_CMD_CABCCTRL        0xC7        /**< cabc control command */
#define ST7789_CMD_REGSEL1         0xC8        /**< register value selection1 command */
#define ST7789_CMD_REGSEL2         0xCA        /**< register value selection2 command */
#define ST7789_CMD_PWMFRSEL        0xCC        /**< pwm frequency selection command */
#define ST7789_CMD_PWCTRL1         0xD0        /**< power control 1 command */
#define ST7789_CMD_VAPVANEN        0xD2        /**< enable vap/van signal output command */
#define ST7789_CMD_CMD2EN          0xDF        /**< command 2 enable command */
#define ST7789_CMD_PVGAMCTRL       0xE0        /**< positive voltage gamma control command */
#define ST7789_CMD_NVGAMCTRL       0xE1        /**< negative voltage gamma control command */
#define ST7789_CMD_DGMLUTR         0xE2        /**< digital gamma look-up table for red command */
#define ST7789_CMD_DGMLUTB         0xE3        /**< digital gamma look-up table for blue command */
#define ST7789_CMD_GATECTRL        0xE4        /**< gate control command */
#define ST7789_CMD_SPI2EN          0xE7        /**< spi2 command */
#define ST7789_CMD_PWCTRL2         0xE8        /**< power control 2 command */
#define ST7789_CMD_EQCTRL          0xE9        /**< equalize time control command */
#define ST7789_CMD_PROMCTRL        0xEC        /**< program control command */
#define ST7789_CMD_PROMEN          0xFA        /**< program mode enable command */
#define ST7789_CMD_NVMSET          0xFC        /**< nvm setting command */
#define ST7789_CMD_PROMACT         0xFE        /**< program action command */

/**
 * @brief     write one byte
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] data written data
 * @param[in] cmd data type
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_st7789_write_byte(st7789_handle_t *handle, uint8_t data, uint8_t cmd)
{
    uint8_t res;

    res = handle->cmd_data_gpio_write(cmd);        /* write gpio */
    if (res != 0)                                  /* check result */
    {
        return 1;                                  /* return error */
    }
    res = handle->spi_write_cmd(&data, 1);         /* write data command */
    if (res != 0)                                  /* check result */
    {
        return 1;                                  /* return error */
    }

    return 0;                                      /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @param[in] cmd data type
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_st7789_write_bytes(st7789_handle_t *handle, uint8_t *data, uint16_t len, uint8_t cmd)
{
    uint8_t res;

    res = handle->cmd_data_gpio_write(cmd);         /* write gpio */
    if (res != 0)                                   /* check result */
    {
        return 1;                                   /* return error */
    }
    res = handle->spi_write_cmd(data, len);         /* write data command */
    if (res != 0)                                   /* check result */
    {
        return 1;                                   /* return error */
    }

    return 0;                                       /* success return 0 */
}

/**
 * @brief     nop
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 nop failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_nop(st7789_handle_t *handle)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_NOP, ST7789_CMD) != 0)        /* write nop command */
    {
        handle->debug_print("st7789: write command failed.\n");              /* write command failed */

        return 1;                                                            /* return error */
    }

    return 0;                                                                /* success return 0 */
}

/**
 * @brief     software reset
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 software reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_software_reset(st7789_handle_t *handle)
{
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_SWRESET, ST7789_CMD) != 0)        /* write software reset command */
    {
        handle->debug_print("st7789: write command failed.\n");                  /* write command failed */

        return 1;                                                                /* return error */
    }
    handle->delay_ms(200);                                                       /* delay 200ms */

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief     sleep in
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 sleep in failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_sleep_in(st7789_handle_t *handle)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_SLPIN, ST7789_CMD) != 0)        /* write sleep in command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     sleep out
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 sleep out failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_sleep_out(st7789_handle_t *handle)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_SLPOUT, ST7789_CMD) != 0)        /* write sleep out command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }
    handle->delay_ms(200);                                                      /* delay 200ms */

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     partial display mode on
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 partial display mode on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_partial_display_mode_on(st7789_handle_t *handle)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PTLON, ST7789_CMD) != 0)        /* write partial display mode on command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     normal display mode on
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 normal display mode on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_normal_display_mode_on(st7789_handle_t *handle)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_NORON, ST7789_CMD) != 0)        /* write normal display mode on command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     display inversion off
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 display inversion off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_display_inversion_off(st7789_handle_t *handle)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_INVOFF, ST7789_CMD) != 0)        /* write display inversion off command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     display inversion on
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 display inversion on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_display_inversion_on(st7789_handle_t *handle)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_INVON, ST7789_CMD) != 0)        /* write display inversion on command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set gamma
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] gamma set gamma
 * @return    status code
 *            - 0 success
 *            - 1 set gamma failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_gamma(st7789_handle_t *handle, uint8_t gamma)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_GAMSET, ST7789_CMD) != 0)       /* write set gamma command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }
    if (a_st7789_write_byte(handle, gamma & 0x0F, ST7789_DATA) != 0)           /* write gamma data */
    {
        handle->debug_print("st7789: write data failed.\n");                   /* write data failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     display off
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 display off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_display_off(st7789_handle_t *handle)
{
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_DISPOFF, ST7789_CMD) != 0)        /* write display off command */
    {
        handle->debug_print("st7789: write command failed.\n");                  /* write command failed */

        return 1;                                                                /* return error */
    }

    return 0;                                                                    /* success return 0 */
}

/**
 * @brief     display on
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 display on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_display_on(st7789_handle_t *handle)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_DISPON, ST7789_CMD) != 0)        /* write display on command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     set the column address
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] start_address start address
 * @param[in] end_address end address
 * @return    status code
 *            - 0 success
 *            - 1 set column address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 address is invalid
 *            - 5 start_address >= end_address
 * @note      start_address <= 319 && end_address <= 319 && start_address >= start_address
 */
uint8_t st7789_set_column_address(st7789_handle_t *handle, uint16_t start_address, uint16_t end_address)
{
    uint8_t buf[4];

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    if ((start_address > 319) || (end_address > 319))                          /* check range */
    {
        handle->debug_print("st7789: address is invalid.\n");                  /* address is invalid */

        return 4;                                                              /* return error */
    }
    if (start_address >= end_address)                                          /* check range */
    {
        handle->debug_print("st7789: start_address >= end_address.\n");        /* start_address >= end_address */

        return 5;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_CASET, ST7789_CMD) != 0)        /* write set column address command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }
    buf[0] = (start_address >> 8) & 0xFF;                                      /* start address msb */
    buf[1] = (start_address >> 0) & 0xFF;                                      /* start address lsb */
    buf[2] = (end_address >> 8) & 0xFF;                                        /* end address msb */
    buf[3] = (end_address >> 0) & 0xFF;                                        /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                   /* write data failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set the row address
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] start_address start address
 * @param[in] end_address end address
 * @return    status code
 *            - 0 success
 *            - 1 set row address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 address is invalid
 *            - 5 start_address >= end_address
 * @note      start_address <= 319 && end_address <= 319 && start_address >= start_address
 */
uint8_t st7789_set_row_address(st7789_handle_t *handle, uint16_t start_address, uint16_t end_address)
{
    uint8_t buf[4];

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    if ((start_address > 319) || (end_address > 319))                          /* check range */
    {
        handle->debug_print("st7789: address is invalid.\n");                  /* address is invalid */

        return 4;                                                              /* return error */
    }
    if (start_address >= end_address)                                          /* check range */
    {
        handle->debug_print("st7789: start_address >= end_address.\n");        /* start_address >= end_address */

        return 5;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RASET, ST7789_CMD) != 0)        /* write set row address command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }
    buf[0] = (start_address >> 8) & 0xFF;                                      /* start address msb */
    buf[1] = (start_address >> 0) & 0xFF;                                      /* start address lsb */
    buf[2] = (end_address >> 8) & 0xFF;                                        /* end address msb */
    buf[3] = (end_address >> 0) & 0xFF;                                        /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                   /* write data failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     memory write
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 memory write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_memory_write(st7789_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RAMWR, ST7789_CMD) != 0)        /* write memory write command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }
    if (a_st7789_write_bytes(handle, data, len, ST7789_DATA) != 0)             /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                   /* write data failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set partial areas
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] start_row start row
 * @param[in] end_row end row
 * @return    status code
 *            - 0 success
 *            - 1 set partial areas failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_partial_areas(st7789_handle_t *handle, uint16_t start_row, uint16_t end_row)
{
    uint8_t buf[4];

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PTLAR, ST7789_CMD) != 0)        /* write set partial areas command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }
    buf[0] = (start_row >> 8) & 0xFF;                                          /* start row msb */
    buf[1] = (start_row >> 0) & 0xFF;                                          /* start row lsb */
    buf[2] = (end_row >> 8) & 0xFF;                                            /* end row msb */
    buf[3] = (end_row >> 0) & 0xFF;                                            /* end row lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                   /* write data failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set vertical scrolling
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] top_fixed_area top fixed area line
 * @param[in] scrolling_area scrolling area line
 * @param[in] bottom_fixed_area bottom fixed area line
 * @return    status code
 *            - 0 success
 *            - 1 set vertical scrolling failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_vertical_scrolling(st7789_handle_t *handle, uint16_t top_fixed_area,
                                      uint16_t scrolling_area, uint16_t bottom_fixed_area)
{
    uint8_t buf[6];

    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_VSCRDEF, ST7789_CMD) != 0)      /* write set vertical scrolling definition command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }
    buf[0] = (top_fixed_area >> 8) & 0xFF;                                     /* top fixed area msb */
    buf[1] = (top_fixed_area >> 0) & 0xFF;                                     /* top fixed area lsb */
    buf[2] = (scrolling_area >> 8) & 0xFF;                                     /* scrolling area msb */
    buf[3] = (scrolling_area >> 0) & 0xFF;                                     /* scrolling area lsb */
    buf[4] = (bottom_fixed_area >> 8) & 0xFF;                                  /* bottom fixed area msb */
    buf[5] = (bottom_fixed_area >> 0) & 0xFF;                                  /* bottom fixed area lsb */
    if (a_st7789_write_bytes(handle, buf, 6, ST7789_DATA) != 0)                /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                   /* write data failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     tearing effect line off
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 tearing effect line off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_tearing_effect_line_off(st7789_handle_t *handle)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_TEOFF, ST7789_CMD) != 0)        /* write tearing effect line off command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     tearing effect line on
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] effect tearing effect
 * @return    status code
 *            - 0 success
 *            - 1 tearing effect line on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_tearing_effect_line_on(st7789_handle_t *handle, st7789_tearing_effect_t effect)
{
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_TEON, ST7789_CMD) != 0)        /* write tearing effect line off command */
    {
        handle->debug_print("st7789: write command failed.\n");               /* write command failed */

        return 1;                                                             /* return error */
    }
    if (a_st7789_write_byte(handle, effect, ST7789_DATA) != 0)                /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                  /* write data failed */

        return 1;                                                             /* return error */
    }

    return 0;                                                                 /* success return 0 */
}

/**
 * @brief     set memory data access control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] order memory data access control order
 * @return    status code
 *            - 0 success
 *            - 1 set memory data access control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_memory_data_access_control(st7789_handle_t *handle, uint8_t order)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_MADCTL, ST7789_CMD) != 0)        /* write set memory data access control command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }
    if (a_st7789_write_byte(handle, order, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                    /* write data failed */

        return 1;                                                               /* return error */
    }

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     set the vertical scroll start address
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] start_address start address
 * @return    status code
 *            - 0 success
 *            - 1 set vertical scroll start address failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 address is invalid
 * @note      none
 */
uint8_t st7789_set_vertical_scroll_start_address(st7789_handle_t *handle, uint16_t start_address)
{
    uint8_t buf[2];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (start_address > 319)                                                      /* check range */
    {
        handle->debug_print("st7789: address is invalid.\n");                     /* address is invalid */

        return 4;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_VSCRSADD, ST7789_CMD) != 0)        /* write vertical scrolling start address command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = (start_address >> 8) & 0xFF;                                         /* start address msb */
    buf[1] = (start_address >> 0) & 0xFF;                                         /* start address lsb */
    if (a_st7789_write_bytes(handle, buf, 2, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     idle mode off
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 idle mode off failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_idle_mode_off(st7789_handle_t *handle)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_IDMOFF, ST7789_CMD) != 0)        /* write idle mode off command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     idle mode on
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 idle mode on failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_idle_mode_on(st7789_handle_t *handle)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_IDMON, ST7789_CMD) != 0)        /* write idle mode on command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set interface pixel format
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] rgb rgb interface color format
 * @param[in] control control interface color format
 * @return    status code
 *            - 0 success
 *            - 1 set interface pixel format failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_interface_pixel_format(st7789_handle_t *handle, st7789_rgb_interface_color_format_t rgb,
                                          st7789_control_interface_color_format_t control)
{
    uint8_t data;

    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_COLMOD, ST7789_CMD) != 0)        /* write interface pixel format command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }

    data = (rgb << 4) | (control << 0);                                         /* set pixel format */
    if (a_st7789_write_byte(handle, data, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                    /* write data failed */

        return 1;                                                               /* return error */
    }
    handle->format = data;                                                      /* set format */

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     memory continue write
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 memory continue write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_memory_continue_write(st7789_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RAMWRC, ST7789_CMD) != 0)       /* write memory write continue command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }
    if (a_st7789_write_bytes(handle, data, len, ST7789_DATA) != 0)             /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                   /* write data failed */

        return 1;                                                              /* return error */
    }

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set tear scanline
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] l tear line
 * @return    status code
 *            - 0 success
 *            - 1 set tear scanline failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_tear_scanline(st7789_handle_t *handle, uint16_t l)
{
    uint8_t buf[2];

    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_TESCAN, ST7789_CMD) != 0)        /* write set tear scanline command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }
    buf[0] = (l >> 8) & 0xFF;                                                   /* start line msb */
    buf[1] = (l >> 0) & 0xFF;                                                   /* start line lsb */
    if (a_st7789_write_bytes(handle, buf, 2, ST7789_DATA) != 0)                 /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                    /* write data failed */

        return 1;                                                               /* return error */
    }

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     set display brightness
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] brightness display brightness
 * @return    status code
 *            - 0 success
 *            - 1 set display brightness failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_display_brightness(st7789_handle_t *handle, uint8_t brightness)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_WRDISBV, ST7789_CMD) != 0)       /* write display brightness command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, brightness, ST7789_DATA) != 0)              /* write brightness */
    {
        handle->debug_print("st7789: write data failed.\n");                    /* write data failed */

        return 1;                                                               /* return error */
    }

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     set display control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] brightness_control_block bool value
 * @param[in] display_dimming bool value
 * @param[in] backlight_control bool value
 * @return    status code
 *            - 0 success
 *            - 1 set display control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_display_control(st7789_handle_t *handle, st7789_bool_t brightness_control_block,
                                   st7789_bool_t display_dimming, st7789_bool_t backlight_control)
{
    uint8_t data;

    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_WRCTRLD, ST7789_CMD) != 0)       /* write CTRL display command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }

    data = (brightness_control_block << 5) | (display_dimming << 3)
            | (backlight_control << 2);                                         /* set control data */
    if (a_st7789_write_byte(handle, data, ST7789_DATA) != 0)                    /* write control */
    {
        handle->debug_print("st7789: write data failed.\n");                    /* write data failed */

        return 1;                                                               /* return error */
    }

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     set brightness control and color enhancement
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] color_enhancement bool value
 * @param[in] mode color enhancement mode
 * @param[in] level color enhancement level
 * @return    status code
 *            - 0 success
 *            - 1 set brightness control and color enhancement failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_brightness_control_and_color_enhancement(st7789_handle_t *handle, st7789_bool_t color_enhancement,
                                                            st7789_color_enhancement_mode_t mode, st7789_color_enhancement_level_t level)
{
    uint8_t data;

    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_WRCACE, ST7789_CMD) != 0)       /* write content adaptive brightness control and color enhancement command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }

    data = (color_enhancement << 7) | (level << 4) | (mode << 0);               /* set control data */
    if (a_st7789_write_byte(handle, data, ST7789_DATA) != 0)                    /* write control */
    {
        handle->debug_print("st7789: write data failed.\n");                    /* write data failed */

        return 1;                                                               /* return error */
    }

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     set cabc minimum brightness
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] brightness display brightness
 * @return    status code
 *            - 0 success
 *            - 1 set cabc minimum brightness failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_cabc_minimum_brightness(st7789_handle_t *handle, uint8_t brightness)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_WRCABCMB, ST7789_CMD) != 0)      /* write CABC minimum brightness command */
    {
        handle->debug_print("st7789: write command failed.\n");                 /* write command failed */

        return 1;                                                               /* return error */
    }

    if (a_st7789_write_byte(handle, brightness, ST7789_DATA) != 0)              /* write brightness */
    {
        handle->debug_print("st7789: write data failed.\n");                    /* write data failed */

        return 1;                                                               /* return error */
    }

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     set ram control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] ram_mode ram mode
 * @param[in] display_mode display mode
 * @param[in] frame_type frame type
 * @param[in] data_mode data mode
 * @param[in] bus_width bus width
 * @param[in] pixel_type pixel type
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
                               st7789_pixel_type_t pixel_type)
{
    uint8_t buf[2];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RAMCTRL, ST7789_CMD) != 0)         /* write ram control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = (ram_mode << 4) | (display_mode << 0);                               /* set param1 */
    buf[1] = (frame_type << 4) | (data_mode << 3) |
             (bus_width << 2) | (pixel_type << 0);                                /* set param2 */
    if (a_st7789_write_bytes(handle, buf, 2, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set rgb interface control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] rgb_mode rgb mode
 * @param[in] rgb_if_mode rgb if enable mode
 * @param[in] vspl vspl active level
 * @param[in] hspl hspl active level
 * @param[in] dpl dpl active level
 * @param[in] epl epl active level
 * @param[in] vbp rgb interface vsync back porch setting
 * @param[in] hbp rgb interface hsync back porch setting
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
                                         uint8_t hbp)
{
    uint8_t buf[3];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (vbp > 0x7F)                                                               /* check vbp */
    {
        handle->debug_print("st7789: vbp > 0x7F.\n");                             /* vbp > 0x7F */

        return 4;                                                                 /* return error */
    }
    if (hbp > 0x1F)                                                               /* check hbp */
    {
        handle->debug_print("st7789: hbp > 0x1F.\n");                             /* hbp > 0x1F */

        return 5;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RGBCTRL, ST7789_CMD) != 0)         /* write rgb control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = (rgb_mode << 7) | (rgb_if_mode << 5) |
             (vspl << 3) | (hspl << 2) | (dpl << 1) | (epl << 0);                 /* set param1 */
    buf[1] = vbp & 0x7F;                                                          /* set param2 */
    buf[2] = hbp & 0x1F;                                                          /* set param3 */
    if (a_st7789_write_bytes(handle, buf, 3, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set porch
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] back_porch_normal back porch setting in normal mode
 * @param[in] front_porch_normal front porch setting in normal mode
 * @param[in] separate_porch_enable bool value
 * @param[in] back_porch_idle back porch setting in idle mode
 * @param[in] front_porch_idle front porch setting in idle mode
 * @param[in] back_porch_partial back porch setting in partial mode
 * @param[in] front_porch_partial front porch setting in partial mode
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
                         uint8_t front_porch_partial)
{
    uint8_t buf[5];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (back_porch_normal > 0x7F)                                                 /* check back_porch_normal */
    {
        handle->debug_print("st7789: back_porch_normal > 0x7F.\n");               /* back_porch_normal > 0x7F */

        return 4;                                                                 /* return error */
    }
    if (front_porch_normal > 0x7F)                                                /* check front_porch_normal */
    {
        handle->debug_print("st7789: front_porch_normal > 0x7F.\n");              /* front_porch_normal > 0x7F */

        return 5;                                                                 /* return error */
    }
    if (back_porch_idle > 0xF)                                                    /* check back_porch_idle */
    {
        handle->debug_print("st7789: back_porch_idle > 0xF.\n");                  /* back_porch_idle > 0xF */

        return 6;                                                                 /* return error */
    }
    if (front_porch_idle > 0xF)                                                   /* check front_porch_idle */
    {
        handle->debug_print("st7789: front_porch_idle > 0xF.\n");                 /* front_porch_idle > 0xF */

        return 7;                                                                 /* return error */
    }
    if (back_porch_partial > 0xF)                                                 /* check back_porch_partial */
    {
        handle->debug_print("st7789: back_porch_partial > 0xF.\n");               /* back_porch_partial > 0xF */

        return 8;                                                                 /* return error */
    }
    if (front_porch_partial > 0xF)                                                /* check front_porch_partial */
    {
        handle->debug_print("st7789: front_porch_partial > 0xF.\n");              /* front_porch_partial > 0xF */

        return 9;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PORCTRL, ST7789_CMD) != 0)         /* write porch control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = back_porch_normal;                                                   /* set param1 */
    buf[1] = front_porch_normal;                                                  /* set param2 */
    buf[2] = separate_porch_enable;                                               /* set param3 */
    buf[3] = (back_porch_idle & 0xF) << 4 | (front_porch_idle & 0xF);             /* set param4 */
    buf[4] = (back_porch_partial & 0xF) << 4 | (front_porch_partial & 0xF);       /* set param5 */
    if (a_st7789_write_bytes(handle, buf, 5, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set frame rate control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] separate_fr_control bool value
 * @param[in] div_control frame rate divided control
 * @param[in] idle_mode inversion idle mode
 * @param[in] idle_frame_rate idle frame rate
 * @param[in] partial_mode inversion partial mode
 * @param[in] partial_frame_rate partial frame rate
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
                                      uint8_t partial_frame_rate)
{
    uint8_t buf[3];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (idle_frame_rate > 0x1F)                                                   /* check idle_frame_rate */
    {
        handle->debug_print("st7789: idle_frame_rate > 0x1F.\n");                 /* idle_frame_rate > 0x1F */

        return 4;                                                                 /* return error */
    }
    if (partial_frame_rate > 0x1F)                                                /* check partial_frame_rate */
    {
        handle->debug_print("st7789: partial_frame_rate > 0x1F.\n");              /* partial_frame_rate > 0x1F */

        return 5;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_FRCTRL1, ST7789_CMD) != 0)         /* write frame rate control 1 command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = (separate_fr_control << 4) | (div_control << 0);                     /* set param1 */
    buf[1] = (idle_mode << 5) | ((idle_frame_rate & 0x1F) << 0);                  /* set param2 */
    buf[2] = (partial_mode << 5) | ((partial_frame_rate & 0x1F) << 0);            /* set param3 */
    if (a_st7789_write_bytes(handle, buf, 3, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set partial mode control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] level non-display source output level
 * @param[in] mode non-display area scan mode
 * @param[in] frequency non-display frame frequency
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
                                        st7789_non_display_frame_frequency_t frequency)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PARCTRL, ST7789_CMD) != 0)         /* write partial mode control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = (level << 7) | (mode << 4) | (frequency << 0);                          /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set gate control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] vghs vghs level
 * @param[in] vgls vgls level
 * @return    status code
 *            - 0 success
 *            - 1 set gate control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_gate_control(st7789_handle_t *handle, st7789_vghs_t vghs, st7789_vgls_t vgls)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_GCTRL, ST7789_CMD) != 0)           /* write gate control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = (vghs << 4) | (vgls << 0);                                              /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set gate on timing adjustment
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] gate_on_timing_adjustment gate on timing adjustment
 * @param[in] gate_off_timing_adjustment_rgb gate off timing adjustment in rgb interface
 * @param[in] gate_off_timing_adjustment gate off timing adjustment
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
                                             uint8_t gate_off_timing_adjustment)
{
    uint8_t buf[4];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (gate_on_timing_adjustment > 0x3F)                                         /* check gate_on_timing_adjustment */
    {
        handle->debug_print("st7789: gate_on_timing_adjustment > 0x3F.\n");       /* gate_on_timing_adjustment > 0x3F */

        return 4;                                                                 /* return error */
    }
    if (gate_off_timing_adjustment_rgb > 0xF)                                     /* check gate_off_timing_adjustment_rgb */
    {
        handle->debug_print("st7789: gate_off_timing_adjustment_rgb > 0xF.\n");   /* gate_off_timing_adjustment_rgb > 0xF */

        return 5;                                                                 /* return error */
    }
    if (gate_off_timing_adjustment > 0xF)                                         /* check gate_off_timing_adjustment */
    {
        handle->debug_print("st7789: gate_off_timing_adjustment > 0xF.\n");       /* gate_off_timing_adjustment > 0xF */

        return 6;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_GTADJ, ST7789_CMD) != 0)           /* write gate on timing adjustment command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = 0x2A;                                                                /* set param1 */
    buf[1] = 0x2B;                                                                /* set param2 */
    buf[2] = gate_on_timing_adjustment & 0x3F;                                    /* set param3 */
    buf[3] = ((gate_off_timing_adjustment_rgb & 0xF) << 4) |
             ((gate_off_timing_adjustment & 0xF) << 0);                           /* set param4 */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     enable or disable digital gamma
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set digital gamma failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_digital_gamma(st7789_handle_t *handle, st7789_bool_t enable)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_DGMEN, ST7789_CMD) != 0)           /* write digital gamma enable command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = enable << 2;                                                            /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set vcoms
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] vcoms set vcoms
 * @return    status code
 *            - 0 success
 *            - 1 set vcoms failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vcoms > 0x3F
 * @note      0 <= vcoms <= 0x3F
 */
uint8_t st7789_set_vcoms(st7789_handle_t *handle, uint8_t vcoms)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (vcoms > 0x3F)                                                             /* check vcoms */
    {
        handle->debug_print("st7789: vcoms > 0x3F.\n");                           /* vcoms > 0x3F */

        return 4;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_VCOMS, ST7789_CMD) != 0)           /* write vcoms setting command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = vcoms & 0x3F;                                                           /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief      convert the vcom to the register raw data
 * @param[in]  *handle pointer to an st7789 handle structure
 * @param[in]  v vcom
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vcom_convert_to_register(st7789_handle_t *handle, float v, uint8_t *reg)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }
    if (handle->inited != 1)                      /* check handle initialization */
    {
        return 3;                                 /* return error */
    }

    *reg = (uint8_t)((v - 0.1f) / 0.025f);        /* convert real data to register data */

    return 0;                                     /* success return 0 */
}

/**
 * @brief      convert the register raw data to the vcom
 * @param[in]  *handle pointer to an st7789 handle structure
 * @param[in]  reg register raw data
 * @param[out] *v pointer to a vcom buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vcom_convert_to_data(st7789_handle_t *handle, uint8_t reg, float *v)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    }

    *v = (uint8_t)((float)(reg) * 0.025f + 0.1f);        /* convert raw data to real data */

    return 0;                                            /* success return 0 */
}

/**
 * @brief     set lcm control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] xmy bool value
 * @param[in] xbgr bool value
 * @param[in] xinv bool value
 * @param[in] xmx bool value
 * @param[in] xmh bool value
 * @param[in] xmv bool value
 * @param[in] xgs bool value
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
                               st7789_bool_t xgs)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_LCMCTRL, ST7789_CMD) != 0)         /* write lcm control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = (xmy << 6) | (xbgr << 5) | (xinv << 4) | (xmx << 3) |
          (xmh << 2) | (xmv << 1) | (xgs << 0);                                   /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set id code setting
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] *id pointer to an id buffer
 * @return    status code
 *            - 0 success
 *            - 1 set id code setting failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_id_code_setting(st7789_handle_t *handle, uint8_t id[3])
{
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_IDSET, ST7789_CMD) != 0)           /* write id setting command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    if (a_st7789_write_bytes(handle, id, 3, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set vdv vrh from
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] from vdv and vrh from
 * @return    status code
 *            - 0 success
 *            - 1 set vdv vrh from failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_vdv_vrh_from(st7789_handle_t *handle, st7789_vdv_vrh_from_t from)
{
    uint8_t buf[2];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_VDVVRHEN, ST7789_CMD) != 0)        /* write vdv and vrh command enable command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = from;                                                                /* set param1 */
    buf[1] = 0xFF;                                                                /* set param2 */
    if (a_st7789_write_bytes(handle, buf, 2, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set vrhs
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] vrhs set vrhs
 * @return    status code
 *            - 0 success
 *            - 1 set vrhs failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vrhs > 0x27
 * @note      0 <= vrhs <= 0x27
 */
uint8_t st7789_set_vrhs(st7789_handle_t *handle, uint8_t vrhs)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (vrhs > 0x27)                                                              /* check vrhs */
    {
        handle->debug_print("st7789: vrhs > 0x27.\n");                            /* vrhs > 0x27 */

        return 4;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_VRHS, ST7789_CMD) != 0)            /* write vrh set command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = vrhs & 0x3F;                                                            /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief      convert the vrhs to the register raw data
 * @param[in]  *handle pointer to an st7789 handle structure
 * @param[in]  v vcom
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vrhs_convert_to_register(st7789_handle_t *handle, float v, uint8_t *reg)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }
    if (handle->inited != 1)                      /* check handle initialization */
    {
        return 3;                                 /* return error */
    }

    *reg = (uint8_t)((v - 3.55f) / 0.05f);        /* convert real data to register data */

    return 0;                                     /* success return 0 */
}

/**
 * @brief      convert the register raw data to the vrhs
 * @param[in]  *handle pointer to an st7789 handle structure
 * @param[in]  reg register raw data
 * @param[out] *v pointer to a vcom buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vrhs_convert_to_data(st7789_handle_t *handle, uint8_t reg, float *v)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    }

    *v = (uint8_t)((float)(reg) * 0.05f + 3.55f);        /* convert raw data to real data */

    return 0;                                            /* success return 0 */
}

/**
 * @brief     set vdv
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] vdv set vdv
 * @return    status code
 *            - 0 success
 *            - 1 set vdv failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 vdv > 0x3F
 * @note      0 <= vdv <= 0x3F
 */
uint8_t st7789_set_vdv(st7789_handle_t *handle, uint8_t vdv)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (vdv > 0x3F)                                                               /* check vdv */
    {
        handle->debug_print("st7789: vdv > 0x3F.\n");                             /* vdv > 0x3F */

        return 4;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_VDVSET, ST7789_CMD) != 0)          /* write vdv setting command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = vdv & 0x3F;                                                             /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief      convert the vdv to the register raw data
 * @param[in]  *handle pointer to an st7789 handle structure
 * @param[in]  v vcom
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vdv_convert_to_register(st7789_handle_t *handle, float v, uint8_t *reg)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }
    if (handle->inited != 1)                      /* check handle initialization */
    {
        return 3;                                 /* return error */
    }

    *reg = (uint8_t)((v + 0.8f) / 0.025f);        /* convert real data to register data */

    return 0;                                     /* success return 0 */
}

/**
 * @brief      convert the register raw data to the vdv
 * @param[in]  *handle pointer to an st7789 handle structure
 * @param[in]  reg register raw data
 * @param[out] *v pointer to a vcom buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vdv_convert_to_data(st7789_handle_t *handle, uint8_t reg, float *v)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    }

    *v = (uint8_t)((float)(reg) * 0.025f - 0.8f);        /* convert raw data to real data */

    return 0;                                            /* success return 0 */
}

/**
 * @brief     set vcoms offset
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] offset vcoms offset
 * @return    status code
 *            - 0 success
 *            - 1 set vcoms offset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 offset > 0x3F
 * @note      0 <= offset <= 0x3F
 */
uint8_t st7789_set_vcoms_offset(st7789_handle_t *handle, uint8_t offset)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (offset > 0x3F)                                                            /* check offset */
    {
        handle->debug_print("st7789: offset > 0x3F.\n");                          /* offset > 0x3F */

        return 4;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_VCMOFSET, ST7789_CMD) != 0)        /* write vcoms offset set command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = offset & 0x3F;                                                          /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief      convert the vcoms offset to the register raw data
 * @param[in]  *handle pointer to an st7789 handle structure
 * @param[in]  v vcoms offset
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vcoms_offset_convert_to_register(st7789_handle_t *handle, float v, uint8_t *reg)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }
    if (handle->inited != 1)                      /* check handle initialization */
    {
        return 3;                                 /* return error */
    }

    *reg = (uint8_t)((v + 0.8f) / 0.025f);        /* convert real data to register data */

    return 0;                                     /* success return 0 */
}

/**
 * @brief      convert the register raw data to the vcoms offset
 * @param[in]  *handle pointer to an st7789 handle structure
 * @param[in]  reg register raw data
 * @param[out] *v pointer to a vcoms offset buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_vcoms_offset_convert_to_data(st7789_handle_t *handle, uint8_t reg, float *v)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    }

    *v = (uint8_t)((float)(reg) * 0.025f - 0.8f);        /* convert raw data to real data */

    return 0;                                            /* success return 0 */
}

/**
 * @brief     set frame rate
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] selection inversion selection
 * @param[in] rate frame rate
 * @return    status code
 *            - 0 success
 *            - 1 set frame rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_frame_rate(st7789_handle_t *handle, st7789_inversion_selection_t selection, st7789_frame_rate_t rate)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_FRCTR2, ST7789_CMD) != 0)          /* write fr control 2 command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = (selection << 5) | (rate << 0);                                         /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set cabc control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] led_on bool value
 * @param[in] led_pwm_init bool value
 * @param[in] led_pwm_fix bool value
 * @param[in] led_pwm_polarity bool value
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
                                st7789_bool_t led_pwm_polarity)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_CABCCTRL, ST7789_CMD) != 0)        /* write cabc control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = (led_on << 3) | (led_pwm_init << 2) |
          (led_pwm_fix << 1) | (led_pwm_polarity << 0);                           /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set pwm frequency
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] frequency pwm frequency
 * @return    status code
 *            - 0 success
 *            - 1 set pwm frequency failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_pwm_frequency(st7789_handle_t *handle, st7789_pwm_frequency_t frequency)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PWMFRSEL, ST7789_CMD) != 0)        /* write pwm frequency selection command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = frequency;                                                              /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set power control 1
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] avdd avdd param
 * @param[in] avcl avcl param
 * @param[in] vds vds param
 * @return    status code
 *            - 0 success
 *            - 1 set power control 1 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_power_control_1(st7789_handle_t *handle, st7789_avdd_t avdd, st7789_avcl_t avcl, st7789_vds_t vds)
{
    uint8_t buf[2];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PWCTRL1, ST7789_CMD) != 0)         /* write power control 1 command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = 0xA4;                                                                /* set param 1 */
    buf[1] = (avdd << 6) | (avcl << 4) | (vds << 0);                              /* set param 2 */
    if (a_st7789_write_bytes(handle, buf, 2, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     enable vap van signal output
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 enable vap van signal output failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_enable_vap_van_signal_output(st7789_handle_t *handle)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_VAPVANEN, ST7789_CMD) != 0)        /* write enable vap/van signal output command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = 0x4C;                                                                   /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     enable or disable command 2
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set command 2 enable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_command_2_enable(st7789_handle_t *handle, st7789_bool_t enable)
{
    uint8_t buf[4];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_CMD2EN, ST7789_CMD) != 0)          /* write command 2 enable command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = 0x5A;                                                                /* set param 1 */
    buf[1] = 0x69;                                                                /* set param 2 */
    buf[2] = 0x02;                                                                /* set param 3 */
    buf[3] = enable;                                                              /* set param 4 */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set positive voltage gamma control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] *param pointer to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 set positive voltage gamma control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_positive_voltage_gamma_control(st7789_handle_t *handle, uint8_t param[14])
{
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PVGAMCTRL, ST7789_CMD) != 0)       /* write positive voltage gamma control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    if (a_st7789_write_bytes(handle, param, 14, ST7789_DATA) != 0)                /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set negative voltage gamma control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] *param pointer to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 set negative voltage gamma control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_negative_voltage_gamma_control(st7789_handle_t *handle, uint8_t param[14])
{
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_NVGAMCTRL, ST7789_CMD) != 0)       /* write negative voltage gamma control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    if (a_st7789_write_bytes(handle, param, 14, ST7789_DATA) != 0)                /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set red digital gamma look up table
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] *param pointer to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 set digital gamma look up table red failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_digital_gamma_look_up_table_red(st7789_handle_t *handle, uint8_t param[64])
{
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_DGMLUTR, ST7789_CMD) != 0)         /* write digital gamma look-up table for red command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    if (a_st7789_write_bytes(handle, param, 64, ST7789_DATA) != 0)                /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set blue digital gamma look up table
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] *param pointer to a param buffer
 * @return    status code
 *            - 0 success
 *            - 1 set digital gamma look up table blue failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_digital_gamma_look_up_table_blue(st7789_handle_t *handle, uint8_t param[64])
{
    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_DGMLUTB, ST7789_CMD) != 0)         /* write digital gamma look-up table for blue command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    if (a_st7789_write_bytes(handle, param, 64, ST7789_DATA) != 0)                /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set gate
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] gate_line_number gate line number
 * @param[in] first_scan_line_number first scan line number
 * @param[in] mode gate scan mode
 * @param[in] direction gate scan direction
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
                        st7789_gate_scan_direction_t direction)
{
    uint8_t buf[3];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (gate_line_number > 0x3F)                                                  /* check gate_line_number */
    {
        handle->debug_print("st7789: gate_line_number > 0x3F.\n");                /* gate_line_number > 0x3F */

        return 4;                                                                 /* return error */
    }
    if (first_scan_line_number > 0x3F)                                            /* check first_scan_line_number */
    {
        handle->debug_print("st7789: first_scan_line_number > 0x3F.\n");          /* first_scan_line_number > 0x3F */

        return 5;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_GATECTRL, ST7789_CMD) != 0)        /* write gate control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = gate_line_number;                                                    /* set param 1 */
    buf[1] = first_scan_line_number;                                              /* set param 2 */
    buf[2] = 0x10 | (mode << 2) | (direction << 0);                               /* set param 3 */
    if (a_st7789_write_bytes(handle, buf, 3, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief      convert the gate line to the register raw data
 * @param[in]  *handle pointer to an st7789 handle structure
 * @param[in]  l gate line
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_gate_line_convert_to_register(st7789_handle_t *handle, uint16_t l, uint8_t *reg)
{
    if (handle == NULL)                       /* check handle */
    {
        return 2;                             /* return error */
    }
    if (handle->inited != 1)                  /* check handle initialization */
    {
        return 3;                             /* return error */
    }

    *reg = (uint8_t)((l / 8) - 1);            /* convert real data to register data */

    return 0;                                 /* success return 0 */
}

/**
 * @brief      convert the register raw data to the gate line
 * @param[in]  *handle pointer to an st7789 handle structure
 * @param[in]  reg register raw data
 * @param[out] *l pointer to a gate line buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t st7789_gate_line_convert_to_data(st7789_handle_t *handle, uint8_t reg, uint16_t *l)
{
    if (handle == NULL)                    /* check handle */
    {
        return 2;                          /* return error */
    }
    if (handle->inited != 1)               /* check handle initialization */
    {
        return 3;                          /* return error */
    }

    *l = (uint8_t)(reg * 8 + 8);           /* convert raw data to real data */

    return 0;                              /* success return 0 */
}

/**
 * @brief     set spi2 enable
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] date_lane bool value
 * @param[in] command_table_2 bool value
 * @return    status code
 *            - 0 success
 *            - 1 set spi2 enable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_spi2_enable(st7789_handle_t *handle, st7789_bool_t date_lane, st7789_bool_t command_table_2)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_SPI2EN, ST7789_CMD) != 0)          /* write spi2 command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = (date_lane << 4) | (command_table_2 << 0);                              /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set power control 2
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] sbclk sbclk div
 * @param[in] stp14ck stp14ck div
 * @return    status code
 *            - 0 success
 *            - 1 set power control 2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_power_control_2(st7789_handle_t *handle, st7789_sbclk_div_t sbclk, st7789_stp14ck_div_t stp14ck)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PWCTRL2, ST7789_CMD) != 0)         /* write power control 2 command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = (sbclk << 4) | (stp14ck << 0);                                          /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set equalize time control
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] source_equalize_time source equalize time
 * @param[in] source_pre_drive_time source pre drive time
 * @param[in] gate_equalize_time gate equalize time
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
                                         uint8_t gate_equalize_time)
{
    uint8_t buf[3];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }
    if (source_equalize_time > 0x1F)                                              /* check source_equalize_time */
    {
        handle->debug_print("st7789: source_equalize_time > 0x1F.\n");            /* source_equalize_time > 0x1F */

        return 4;                                                                 /* return error */
    }
    if (source_pre_drive_time > 0x1F)                                             /* check source_pre_drive_time */
    {
        handle->debug_print("st7789: source_pre_drive_time > 0x1F.\n");           /* source_pre_drive_time > 0x1F */

        return 5;                                                                 /* return error */
    }
    if (gate_equalize_time > 0xF)                                                 /* check gate_equalize_time */
    {
        handle->debug_print("st7789: gate_equalize_time > 0xF.\n");               /* gate_equalize_time > 0xF */

        return 6;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_EQCTRL, ST7789_CMD) != 0)          /* write equalize time control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = source_equalize_time;                                                /* set param 1 */
    buf[1] = source_pre_drive_time;                                               /* set param 2 */
    buf[2] = gate_equalize_time;                                                  /* set param 3 */
    if (a_st7789_write_bytes(handle, buf, 3, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set program mode control
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set program mode control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_program_mode_control(st7789_handle_t *handle)
{
    uint8_t reg;

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PROMCTRL, ST7789_CMD) != 0)        /* write program control command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    reg = 0x01;                                                                   /* set param */
    if (a_st7789_write_byte(handle, reg, ST7789_DATA) != 0)                       /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     enable or disable program mode
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set program mode enable failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_program_mode_enable(st7789_handle_t *handle, st7789_bool_t enable)
{
    uint8_t buf[4];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PROMEN, ST7789_CMD) != 0)          /* write program mode enable command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = 0x5A;                                                                /* set param 1 */
    buf[1] = 0x69;                                                                /* set param 2 */
    buf[2] = 0xEE;                                                                /* set param 3 */
    buf[3] = enable << 2;                                                         /* set param 4 */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set nvm setting
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] addr nvm address
 * @param[in] data nvm set data
 * @return    status code
 *            - 0 success
 *            - 1 set nvm setting failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_nvm_setting(st7789_handle_t *handle, uint8_t addr, uint8_t data)
{
    uint8_t buf[2];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_NVMSET, ST7789_CMD) != 0)          /* write nvm setting command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = addr;                                                                /* set param 1 */
    buf[1] = data;                                                                /* set param 2 */
    if (a_st7789_write_bytes(handle, buf, 2, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     set program action
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 set program action failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_set_program_action(st7789_handle_t *handle)
{
    uint8_t buf[2];

    if (handle == NULL)                                                           /* check handle */
    {
        return 2;                                                                 /* return error */
    }
    if (handle->inited != 1)                                                      /* check handle initialization */
    {
        return 3;                                                                 /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_PROMACT, ST7789_CMD) != 0)         /* write program action command */
    {
        handle->debug_print("st7789: write command failed.\n");                   /* write command failed */

        return 1;                                                                 /* return error */
    }
    buf[0] = 0x29;                                                                /* set param 1 */
    buf[1] = 0xA5;                                                                /* set param 2 */
    if (a_st7789_write_bytes(handle, buf, 2, ST7789_DATA) != 0)                   /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                      /* write data failed */

        return 1;                                                                 /* return error */
    }

    return 0;                                                                     /* success return 0 */
}

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset failed
 *            - 5 command && data init failed
 * @note      none
 */
uint8_t st7789_init(st7789_handle_t *handle)
{
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->debug_print == NULL)                                            /* check debug_print */
    {
        return 3;                                                               /* return error */
    }
    if (handle->spi_init == NULL)                                               /* check spi_init */
    {
        handle->debug_print("st7789: spi_init is null.\n");                     /* spi_init is null */

        return 3;                                                               /* return error */
    }
    if (handle->spi_deinit == NULL)                                             /* check spi_deinit */
    {
        handle->debug_print("st7789: spi_deinit is null.\n");                   /* spi_deinit is null */

        return 3;                                                               /* return error */
    }
    if (handle->spi_write_cmd == NULL)                                          /* check spi_write_cmd */
    {
        handle->debug_print("st7789: spi_write_cmd is null.\n");                /* spi_init is null */

        return 3;                                                               /* return error */
    }
    if (handle->cmd_data_gpio_init == NULL)                                     /* check cmd_data_gpio_init */
    {
        handle->debug_print("st7789: cmd_data_gpio_init is null.\n");           /* cmd_data_gpio_init is null */

        return 3;                                                               /* return error */
    }
    if (handle->cmd_data_gpio_deinit == NULL)                                   /* check cmd_data_gpio_deinit */
    {
        handle->debug_print("st7789: cmd_data_gpio_deinit is null.\n");         /* cmd_data_gpio_deinit is null */

        return 3;                                                               /* return error */
    }
    if (handle->cmd_data_gpio_write == NULL)                                    /* check cmd_data_gpio_write */
    {
        handle->debug_print("st7789: cmd_data_gpio_write is null.\n");          /* cmd_data_gpio_write is null */

        return 3;                                                               /* return error */
    }
    if (handle->reset_gpio_init == NULL)                                        /* check reset_gpio_init */
    {
        handle->debug_print("st7789: reset_gpio_init is null.\n");              /* reset_gpio_init is null */

        return 3;                                                               /* return error */
    }
    if (handle->reset_gpio_deinit == NULL)                                      /* check reset_gpio_deinit */
    {
        handle->debug_print("st7789: reset_gpio_deinit is null.\n");            /* reset_gpio_deinit is null */

        return 3;                                                               /* return error */
    }
    if (handle->reset_gpio_write == NULL)                                       /* check reset_gpio_write */
    {
        handle->debug_print("st7789: reset_gpio_write is null.\n");             /* reset_gpio_write is null */

        return 3;                                                               /* return error */
    }
    if (handle->delay_ms == NULL)                                               /* check delay_ms */
    {
        handle->debug_print("st7789: delay_ms is null.\n");                     /* delay_ms is null */

        return 3;                                                               /* return error */
    }

    if (handle->cmd_data_gpio_init() != 0)                                      /* check cmd_data_gpio_init */
    {
        handle->debug_print("st7789: cmd data gpio init failed.\n");            /* cmd data gpio init failed */

        return 5;                                                               /* return error */
    }
    if (handle->reset_gpio_init() != 0)                                         /* reset gpio init */
    {
        handle->debug_print("st7789: reset gpio init failed.\n");               /* reset gpio init failed */
        (void)handle->cmd_data_gpio_deinit();                                   /* cmd_data_gpio_deinit */

        return 4;                                                               /* return error */
    }
    if (handle->reset_gpio_write(0) != 0)                                       /* write 0 */
    {
        handle->debug_print("st7789: reset gpio write failed.\n");              /* reset gpio write failed */
        (void)handle->cmd_data_gpio_deinit();                                   /* cmd_data_gpio_deinit */
        (void)handle->reset_gpio_deinit();                                      /* reset_gpio_deinit */

        return 4;                                                               /* return error */
    }
    handle->delay_ms(25);                                                       /* over 10 us */
    if (handle->reset_gpio_write(1) != 0)                                       /* write 1 */
    {
        handle->debug_print("st7789: reset gpio write failed.\n");              /* reset gpio write failed */
        (void)handle->cmd_data_gpio_deinit();                                   /* cmd_data_gpio_deinit */
        (void)handle->reset_gpio_deinit();                                      /* reset_gpio_deinit */

        return 4;                                                               /* return error */
    }
    handle->delay_ms(125);                                                      /* over 120 ms */
    if (handle->spi_init() != 0)                                                /* spi init */
    {
        handle->debug_print("st7789: spi init failed.\n");                      /* spi init failed */
        (void)handle->cmd_data_gpio_deinit();                                   /* cmd_data_gpio_deinit */
        (void)handle->reset_gpio_deinit();                                      /* reset_gpio_deinit */

        return 1;                                                               /* return error */
    }
    handle->inited = 1;                                                         /* flag inited */

    return 0;                                                                   /* success return 0 */
}

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an st7789 handle structure
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
uint8_t st7789_deinit(st7789_handle_t *handle)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_SLPIN, ST7789_CMD) != 0)        /* write sleep in command */
    {
        handle->debug_print("st7789: write command failed.\n");                /* write command failed */

        return 1;                                                              /* return error */
    }
    if (handle->reset_gpio_deinit() != 0)                                      /* reset gpio deinit */
    {
        handle->debug_print("st7789: reset gpio deinit failed.\n");            /* reset gpio deinit failed */

        return 5;                                                              /* return error */
    }
    if (handle->cmd_data_gpio_deinit() != 0)                                   /* cmd data gpio deinit */
    {
        handle->debug_print("st7789: cmd data gpio deinit failed.\n");         /* cmd data gpio deinit failed */

        return 6;                                                              /* return error */
    }
    if (handle->spi_deinit() != 0)                                             /* spi deinit */
    {
        handle->debug_print("st7789: spi deinit failed.\n");                   /* spi deinit failed */

        return 1;                                                              /* return error */
    }
    handle->inited = 0;                                                        /* flag close */

    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     set column
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] column screen column
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 column > 240
 * @note      none
 */
uint8_t st7789_set_column(st7789_handle_t *handle, uint16_t column)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }
    if (column > 240)                                          /* check column */
    {
        handle->debug_print("st7789: column > 240.\n");        /* column > 240 */

        return 4;                                              /* return error */
    }

    handle->column = column;                                   /* set column */

    return 0;                                                  /* success return 0 */
}

/**
 * @brief     set row
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] row screen row
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 row > 320
 * @note      none
 */
uint8_t st7789_set_row(st7789_handle_t *handle, uint16_t row)
{
    if (handle == NULL)                                        /* check handle */
    {
        return 2;                                              /* return error */
    }
    if (handle->inited != 1)                                   /* check handle initialization */
    {
        return 3;                                              /* return error */
    }
    if (row > 320)                                             /* check column */
    {
        handle->debug_print("st7789: row > 320.\n");           /* row > 320 */

        return 4;                                              /* return error */
    }

    handle->row = row;                                         /* set row */

    return 0;                                                  /* success return 0 */
}

/**
 * @brief     clear the display
 * @param[in] *handle pointer to an st7789 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 clear failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 format is invalid
 * @note      none
 */
uint8_t st7789_clear(st7789_handle_t *handle)
{
    uint8_t buf[4];
    uint32_t i;
    uint32_t m;
    uint32_t n;

    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_CASET, ST7789_CMD) != 0)            /* write set column address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (0x00 >> 8) & 0xFF;                                                   /* start address msb */
    buf[1] = (0x00 >> 0) & 0xFF;                                                   /* start address lsb */
    buf[2] = ((handle->column - 1) >> 8) & 0xFF;                                   /* end address msb */
    buf[3] = ((handle->column - 1) >> 0) & 0xFF;                                   /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RASET, ST7789_CMD) != 0)            /* write set row address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (0x00 >> 8) & 0xFF;                                                   /* start address msb */
    buf[1] = (0x00 >> 0) & 0xFF;                                                   /* start address lsb */
    buf[2] = ((handle->row - 1) >> 8) & 0xFF;                                      /* end address msb */
    buf[3] = ((handle->row - 1) >> 0) & 0xFF;                                      /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RAMWR, ST7789_CMD) != 0)            /* write memory write command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }

    if ((handle->format & 0x03) == 0x03)                                           /* rgb444 */
    {
        memset(handle->buf, 0x00, sizeof(uint8_t) * ST7789_BUFFER_SIZE);           /* clear buffer */
        m = ((uint32_t)(handle->row) * handle->column * 3 / 2) /
             ST7789_BUFFER_SIZE;                                                   /* total times */
        n = ((uint32_t)(handle->row) * handle->column * 3 / 2) %
             ST7789_BUFFER_SIZE;                                                   /* the last */
        for (i = 0; i < m; i++)
        {
            if (a_st7789_write_bytes(handle, handle->buf,
                ST7789_BUFFER_SIZE, ST7789_DATA) != 0)                             /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
        if (n != 0)                                                                /* not end */
        {
            if (a_st7789_write_bytes(handle, handle->buf, n, ST7789_DATA) != 0)    /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
    }
    else if ((handle->format & 0x05) == 0x05)                                      /* rgb565 */
    {
        memset(handle->buf, 0x00, sizeof(uint8_t) * ST7789_BUFFER_SIZE);           /* clear buffer */
        m = (uint32_t)(handle->row) * handle->column * 2 / ST7789_BUFFER_SIZE;     /* total times */
        n = (uint32_t)(handle->row) * handle->column * 2 % ST7789_BUFFER_SIZE;     /* the last */
        for (i = 0; i < m; i++)
        {
            if (a_st7789_write_bytes(handle, handle->buf,
                ST7789_BUFFER_SIZE, ST7789_DATA) != 0)                             /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
        if (n != 0)                                                                /* not end */
        {
            if (a_st7789_write_bytes(handle, handle->buf, n, ST7789_DATA) != 0)    /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
    }
    else if ((handle->format & 0x06) == 0x06)                                      /* rgb666 */
    {
        memset(handle->buf, 0x00, sizeof(uint8_t) * ST7789_BUFFER_SIZE);           /* clear buffer */
        m = (uint32_t)(handle->row) * handle->column * 3 / ST7789_BUFFER_SIZE;     /* total times */
        n = (uint32_t)(handle->row) * handle->column * 3 % ST7789_BUFFER_SIZE;     /* the last */
        for (i = 0; i < m; i++)
        {
            if (a_st7789_write_bytes(handle, handle->buf,
                ST7789_BUFFER_SIZE, ST7789_DATA) != 0)                             /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
        if (n != 0)                                                                /* not end */
        {
            if (a_st7789_write_bytes(handle, handle->buf, n, ST7789_DATA) != 0)    /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
    }
    else
    {
        handle->debug_print("st7789: format is invalid.\n");                       /* format is invalid */

        return 4;                                                                  /* return error */
    }

    return 0;                                                                      /* success return 0 */
}

/**
 * @brief     fill the rect
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] left left coordinate x
 * @param[in] top top coordinate y
 * @param[in] right right coordinate x
 * @param[in] bottom bottom coordinate y
 * @param[in] color display color
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
uint8_t st7789_fill_rect(st7789_handle_t *handle, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint32_t color)
{
    uint8_t buf[4];
    uint32_t i;
    uint32_t m;
    uint32_t n;

    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    if (left > (handle->column - 1))                                               /* check left */
    {
        handle->debug_print("st7789: left is over column.\n");                     /* left is over column */

        return 4;                                                                  /* return error */
    }
    if (right > (handle->column - 1))                                              /* check right */
    {
        handle->debug_print("st7789: right is over column.\n");                    /* right is over column */

        return 5;                                                                  /* return error */
    }
    if (left >= right)                                                             /* check left and right */
    {
        handle->debug_print("st7789: left >= right.\n");                           /* left >= right */

        return 6;                                                                  /* return error */
    }
    if (top > (handle->row - 1))                                                   /* check top */
    {
        handle->debug_print("st7789: top is over row.\n");                         /* top is over row */

        return 7;                                                                  /* return error */
    }
    if (bottom > (handle->row - 1))                                                /* check bottom */
    {
        handle->debug_print("st7789: bottom is over row.\n");                      /* bottom is over row */

        return 8;                                                                  /* return error */
    }
    if (top >= bottom)                                                             /* check top and bottom */
    {
        handle->debug_print("st7789: top >= bottom.\n");                           /* top >= bottom */

        return 9;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_CASET, ST7789_CMD) != 0)            /* write set column address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (left >> 8) & 0xFF;                                                   /* start address msb */
    buf[1] = (left >> 0) & 0xFF;                                                   /* start address lsb */
    buf[2] = ((right) >> 8) & 0xFF;                                                /* end address msb */
    buf[3] = ((right) >> 0) & 0xFF;                                                /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RASET, ST7789_CMD) != 0)            /* write set row address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (top >> 8) & 0xFF;                                                    /* start address msb */
    buf[1] = (top >> 0) & 0xFF;                                                    /* start address lsb */
    buf[2] = ((bottom) >> 8) & 0xFF;                                               /* end address msb */
    buf[3] = ((bottom) >> 0) & 0xFF;                                               /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RAMWR, ST7789_CMD) != 0)            /* write memory write command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }

    if ((handle->format & 0x03) == 0x03)                                           /* rgb444 */
    {
        for (i = 0; i < ST7789_BUFFER_SIZE; i += 3)                                /* fill the buffer */
        {
            handle->buf[i] = (((color >> 8) & 0xF) << 4) |
                             (((color >> 4) & 0xF) << 0);                          /* set the color */
            handle->buf[i + 1] = (((color >> 0) & 0xF) << 4) |
                                 (((color >> 8) & 0xF) << 0);                      /* set the color */
            handle->buf[i + 2] = (((color >> 4) & 0xF) << 4) |
                                 (((color >> 0) & 0xF) << 0);                      /* set the color */
        }
        m = ((uint32_t)(right - left + 1) * (bottom - top + 1) * 3 / 2) /
             ST7789_BUFFER_SIZE;                                                   /* total times */
        n = ((uint32_t)(right - left + 1) * (bottom - top + 1) * 3 / 2) %
             ST7789_BUFFER_SIZE;                                                   /* the last */
        for (i = 0; i < m; i++)
        {
            if (a_st7789_write_bytes(handle, handle->buf,
                ST7789_BUFFER_SIZE, ST7789_DATA) != 0)                             /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
        if (n != 0)                                                                /* not end */
        {
            if (a_st7789_write_bytes(handle, handle->buf, n, ST7789_DATA) != 0)    /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
    }
    else if ((handle->format & 0x05) == 0x05)                                      /* rgb565 */
    {
        for (i = 0; i < ST7789_BUFFER_SIZE; i += 2)                                /* fill the buffer */
        {
            handle->buf[i] = (color >> 8) & 0xFF;                                  /* set the color */
            handle->buf[i + 1] = (color >> 0) & 0xFF;                              /* set the color */
        }
        m = (uint32_t)(right - left + 1) * (bottom - top + 1) * 2 /
             ST7789_BUFFER_SIZE;                                                   /* total times */
        n = ((uint32_t)(right - left + 1) * (bottom - top + 1) * 2) %
             ST7789_BUFFER_SIZE;                                                   /* the last */
        for (i = 0; i < m; i++)
        {
            if (a_st7789_write_bytes(handle, handle->buf,
                ST7789_BUFFER_SIZE, ST7789_DATA) != 0)                             /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
        if (n != 0)                                                                /* not end */
        {
            if (a_st7789_write_bytes(handle, handle->buf, n, ST7789_DATA) != 0)    /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
    }
    else if ((handle->format & 0x06) == 0x06)                                      /* rgb666 */
    {
        for (i = 0; i < ST7789_BUFFER_SIZE; i += 3)                                /* fill the buffer */
        {
            handle->buf[i] = ((color >> 12) & 0x3F) << 2;                          /* set the color */
            handle->buf[i + 1] = ((color >> 6) & 0x3F) << 2;                       /* set the color */
            handle->buf[i + 2] = ((color >> 0) & 0x3F) << 2;                       /* set the color */
        }
        m = (uint32_t)(right - left + 1) * (bottom - top + 1) * 3 /
             ST7789_BUFFER_SIZE;                                                   /* total times */
        n = ((uint32_t)(right - left + 1) * (bottom - top + 1) * 3) %
             ST7789_BUFFER_SIZE;                                                   /* the last */
        for (i = 0; i < m; i++)
        {
            if (a_st7789_write_bytes(handle, handle->buf,
                ST7789_BUFFER_SIZE, ST7789_DATA) != 0)                             /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
        if (n != 0)                                                                /* not end */
        {
            if (a_st7789_write_bytes(handle, handle->buf, n, ST7789_DATA) != 0)    /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
    }
    else
    {
        handle->debug_print("st7789: format is invalid.\n");                       /* format is invalid */

        return 4;                                                                  /* return error */
    }

    return 0;                                                                      /* success return 0 */
}

/**
 * @brief     draw a picture
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] left left coordinate x
 * @param[in] top top coordinate y
 * @param[in] right right coordinate x
 * @param[in] bottom bottom coordinate y
 * @param[in] *image pointer to an image buffer
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
uint8_t st7789_draw_picture_12bits(st7789_handle_t *handle, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t *image)
{
    uint8_t buf[4];
    uint32_t i;
    uint32_t j;
    uint32_t m;
    uint32_t n;
    uint32_t point;

    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    if (left > (handle->column - 1))                                               /* check left */
    {
        handle->debug_print("st7789: left is over column.\n");                     /* left is over column */

        return 4;                                                                  /* return error */
    }
    if (right > (handle->column - 1))                                              /* check right */
    {
        handle->debug_print("st7789: right is over column.\n");                    /* right is over column */

        return 5;                                                                  /* return error */
    }
    if (left >= right)                                                             /* check left and right */
    {
        handle->debug_print("st7789: left >= right.\n");                           /* left >= right */

        return 6;                                                                  /* return error */
    }
    if (top > (handle->row - 1))                                                   /* check top */
    {
        handle->debug_print("st7789: top is over row.\n");                         /* top is over row */

        return 7;                                                                  /* return error */
    }
    if (bottom > (handle->row - 1))                                                /* check bottom */
    {
        handle->debug_print("st7789: bottom is over row.\n");                      /* bottom is over row */

        return 8;                                                                  /* return error */
    }
    if (top >= bottom)                                                             /* check top and bottom */
    {
        handle->debug_print("st7789: top >= bottom.\n");                           /* top >= bottom */

        return 9;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_CASET, ST7789_CMD) != 0)            /* write set column address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (left >> 8) & 0xFF;                                                   /* start address msb */
    buf[1] = (left >> 0) & 0xFF;                                                   /* start address lsb */
    buf[2] = ((right) >> 8) & 0xFF;                                                /* end address msb */
    buf[3] = ((right) >> 0) & 0xFF;                                                /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RASET, ST7789_CMD) != 0)            /* write set row address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (top >> 8) & 0xFF;                                                    /* start address msb */
    buf[1] = (top >> 0) & 0xFF;                                                    /* start address lsb */
    buf[2] = ((bottom) >> 8) & 0xFF;                                               /* end address msb */
    buf[3] = ((bottom) >> 0) & 0xFF;                                               /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RAMWR, ST7789_CMD) != 0)            /* write memory write command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }

    if ((handle->format & 0x03) == 0x03)                                           /* rgb444 */
    {
        uint16_t r;
        uint16_t c;
        uint16_t color;

        c = right - left + 1;                                                      /* column */
        r = bottom - top + 1;                                                      /* row */
        point = 0;                                                                 /* image point init 0 */
        m = ((uint32_t)(right - left + 1) * (bottom - top + 1) * 3 / 2) /
             ST7789_BUFFER_SIZE;                                                   /* total times */
        n = ((uint32_t)(right - left + 1) * (bottom - top + 1) * 3 / 2) %
             ST7789_BUFFER_SIZE;                                                   /* the last */
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < ST7789_BUFFER_SIZE; j += 3)                            /* fill the buffer */
            {
                color = image[(point % c) * r + (point / c)];                      /* set color */
                handle->buf[i] = (((color >> 8) & 0xF) << 4) |
                                 (((color >> 4) & 0xF) << 0);                      /* set the color */
                handle->buf[i + 1] = (((color >> 0) & 0xF) << 4) |
                                     (((color >> 8) & 0xF) << 0);                  /* set the color */
                handle->buf[i + 2] = (((color >> 4) & 0xF) << 4) |
                                     (((color >> 0) & 0xF) << 0);                  /* set the color */
                point++;                                                           /* point++ */
            }
            if (a_st7789_write_bytes(handle, handle->buf,
                ST7789_BUFFER_SIZE, ST7789_DATA) != 0)                             /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
        if (n != 0)                                                                /* not end */
        {
            for (j = 0; j < n; j += 3)                                             /* fill the buffer */
            {
                color = image[(point % c) * r + (point / c)];                      /* set color */
                handle->buf[i] = (((color >> 8) & 0xF) << 4) |
                                 (((color >> 4) & 0xF) << 0);                      /* set the color */
                handle->buf[i + 1] = (((color >> 0) & 0xF) << 4) |
                                     (((color >> 8) & 0xF) << 0);                  /* set the color */
                handle->buf[i + 2] = (((color >> 4) & 0xF) << 4) |
                                     (((color >> 0) & 0xF) << 0);                  /* set the color */
                point++;                                                           /* point++ */
            }
            if (a_st7789_write_bytes(handle, handle->buf, n, ST7789_DATA) != 0)    /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
    }
    else
    {
        handle->debug_print("st7789: format is invalid.\n");                       /* format is invalid */

        return 4;                                                                  /* return error */
    }

    return 0;                                                                      /* success return 0 */
}

/**
 * @brief     draw a picture
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] left left coordinate x
 * @param[in] top top coordinate y
 * @param[in] right right coordinate x
 * @param[in] bottom bottom coordinate y
 * @param[in] *image pointer to an image buffer
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
uint8_t st7789_draw_picture_16bits(st7789_handle_t *handle, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t *image)
{
    uint8_t buf[4];
    uint32_t i;
    uint32_t j;
    uint32_t m;
    uint32_t n;
    uint32_t point;

    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    if (left > (handle->column - 1))                                               /* check left */
    {
        handle->debug_print("st7789: left is over column.\n");                     /* left is over column */

        return 4;                                                                  /* return error */
    }
    if (right > (handle->column - 1))                                              /* check right */
    {
        handle->debug_print("st7789: right is over column.\n");                    /* right is over column */

        return 5;                                                                  /* return error */
    }
    if (left >= right)                                                             /* check left and right */
    {
        handle->debug_print("st7789: left >= right.\n");                           /* left >= right */

        return 6;                                                                  /* return error */
    }
    if (top > (handle->row - 1))                                                   /* check top */
    {
        handle->debug_print("st7789: top is over row.\n");                         /* top is over row */

        return 7;                                                                  /* return error */
    }
    if (bottom > (handle->row - 1))                                                /* check bottom */
    {
        handle->debug_print("st7789: bottom is over row.\n");                      /* bottom is over row */

        return 8;                                                                  /* return error */
    }
    if (top >= bottom)                                                             /* check top and bottom */
    {
        handle->debug_print("st7789: top >= bottom.\n");                           /* top >= bottom */

        return 9;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_CASET, ST7789_CMD) != 0)            /* write set column address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (left >> 8) & 0xFF;                                                   /* start address msb */
    buf[1] = (left >> 0) & 0xFF;                                                   /* start address lsb */
    buf[2] = ((right) >> 8) & 0xFF;                                                /* end address msb */
    buf[3] = ((right) >> 0) & 0xFF;                                                /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RASET, ST7789_CMD) != 0)            /* write set row address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (top >> 8) & 0xFF;                                                    /* start address msb */
    buf[1] = (top >> 0) & 0xFF;                                                    /* start address lsb */
    buf[2] = ((bottom) >> 8) & 0xFF;                                               /* end address msb */
    buf[3] = ((bottom) >> 0) & 0xFF;                                               /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RAMWR, ST7789_CMD) != 0)            /* write memory write command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }

    if ((handle->format & 0x05) == 0x05)                                           /* rgb565 */
    {
        uint16_t r;
        uint16_t c;
        uint16_t color;

        c = right - left + 1;                                                      /* column */
        r = bottom - top + 1;                                                      /* row */
        point = 0;                                                                 /* image point init 0 */
        m = ((uint32_t)(right - left + 1) * (bottom - top + 1) * 2) /
             ST7789_BUFFER_SIZE;                                                   /* total times */
        n = ((uint32_t)(right - left + 1) * (bottom - top + 1) * 2) %
             ST7789_BUFFER_SIZE;                                                   /* the last */
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < ST7789_BUFFER_SIZE; j += 2)                            /* fill the buffer */
            {
                color = image[(point % c) * r + (point / c)];                      /* set color */
                handle->buf[j] = (color >> 8) & 0xFF;                              /* set the color */
                handle->buf[j + 1] = (color >> 0) & 0xFF;                          /* set the color */
                point++;                                                           /* point++ */
            }
            if (a_st7789_write_bytes(handle, handle->buf,
                ST7789_BUFFER_SIZE, ST7789_DATA) != 0)                             /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
        if (n != 0)                                                                /* not end */
        {
            for (j = 0; j < n; j += 2)                                             /* fill the buffer */
            {
                color = image[(point % c) * r + (point / c)];                      /* set color */
                handle->buf[j] = (color >> 8) & 0xFF;                              /* set the color */
                handle->buf[j + 1] = (color >> 0) & 0xFF;                          /* set the color */
                point++;                                                           /* point++ */
            }
            if (a_st7789_write_bytes(handle, handle->buf, n, ST7789_DATA) != 0)    /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
    }
    else
    {
        handle->debug_print("st7789: format is invalid.\n");                       /* format is invalid */

        return 4;                                                                  /* return error */
    }

    return 0;                                                                      /* success return 0 */
}

/**
 * @brief     draw a picture
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] left left coordinate x
 * @param[in] top top coordinate y
 * @param[in] right right coordinate x
 * @param[in] bottom bottom coordinate y
 * @param[in] *image pointer to an image buffer
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
uint8_t st7789_draw_picture_18bits(st7789_handle_t *handle, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint32_t *image)
{
    uint8_t buf[4];
    uint32_t i;
    uint32_t j;
    uint32_t m;
    uint32_t n;
    uint32_t point;

    if (handle == NULL)                                                            /* check handle */
    {
        return 2;                                                                  /* return error */
    }
    if (handle->inited != 1)                                                       /* check handle initialization */
    {
        return 3;                                                                  /* return error */
    }
    if (left > (handle->column - 1))                                               /* check left */
    {
        handle->debug_print("st7789: left is over column.\n");                     /* left is over column */

        return 4;                                                                  /* return error */
    }
    if (right > (handle->column - 1))                                              /* check right */
    {
        handle->debug_print("st7789: right is over column.\n");                    /* right is over column */

        return 5;                                                                  /* return error */
    }
    if (left >= right)                                                             /* check left and right */
    {
        handle->debug_print("st7789: left >= right.\n");                           /* left >= right */

        return 6;                                                                  /* return error */
    }
    if (top > (handle->row - 1))                                                   /* check top */
    {
        handle->debug_print("st7789: top is over row.\n");                         /* top is over row */

        return 7;                                                                  /* return error */
    }
    if (bottom > (handle->row - 1))                                                /* check bottom */
    {
        handle->debug_print("st7789: bottom is over row.\n");                      /* bottom is over row */

        return 8;                                                                  /* return error */
    }
    if (top >= bottom)                                                             /* check top and bottom */
    {
        handle->debug_print("st7789: top >= bottom.\n");                           /* top >= bottom */

        return 9;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_CASET, ST7789_CMD) != 0)            /* write set column address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (left >> 8) & 0xFF;                                                   /* start address msb */
    buf[1] = (left >> 0) & 0xFF;                                                   /* start address lsb */
    buf[2] = ((right) >> 8) & 0xFF;                                                /* end address msb */
    buf[3] = ((right) >> 0) & 0xFF;                                                /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RASET, ST7789_CMD) != 0)            /* write set row address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (top >> 8) & 0xFF;                                                    /* start address msb */
    buf[1] = (top >> 0) & 0xFF;                                                    /* start address lsb */
    buf[2] = ((bottom) >> 8) & 0xFF;                                               /* end address msb */
    buf[3] = ((bottom) >> 0) & 0xFF;                                               /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RAMWR, ST7789_CMD) != 0)            /* write memory write command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }

    if ((handle->format & 0x06) == 0x06)                                           /* rgb666 */
    {
        uint16_t r;
        uint16_t c;
        uint32_t color;

        c = right - left + 1;                                                      /* column */
        r = bottom - top + 1;                                                      /* row */
        point = 0;                                                                 /* image point init 0 */
        m = ((uint32_t)(right - left + 1) * (bottom - top + 1) * 3) /
             ST7789_BUFFER_SIZE;                                                   /* total times */
        n = ((uint32_t)(right - left + 1) * (bottom - top + 1) * 3) %
             ST7789_BUFFER_SIZE;                                                   /* the last */
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < ST7789_BUFFER_SIZE; j += 3)                            /* fill the buffer */
            {
                color = image[(point % c) * r + (point / c)];                      /* set color */
                handle->buf[j] = ((color >> 12) & 0x3F) << 2;                      /* set the color */
                handle->buf[j + 1] = ((color >> 6) & 0x3F) << 2;                   /* set the color */
                handle->buf[j + 2] = ((color >> 0) & 0x3F) << 2;                   /* set the color */
                point++;                                                           /* point++ */
            }
            if (a_st7789_write_bytes(handle, handle->buf,
                ST7789_BUFFER_SIZE, ST7789_DATA) != 0)                             /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
        if (n != 0)                                                                /* not end */
        {
            for (j = 0; j < n; j += 3)                                             /* fill the buffer */
            {
                color = image[(point % c) * r + (point / c)];                      /* set color */
                handle->buf[j] = ((color >> 12) & 0x3F) << 2;                      /* set the color */
                handle->buf[j + 1] = ((color >> 6) & 0x3F) << 2;                   /* set the color */
                handle->buf[j + 2] = ((color >> 0) & 0x3F) << 2;                   /* set the color */
                point++;                                                           /* point++ */
            }
            if (a_st7789_write_bytes(handle, handle->buf, n, ST7789_DATA) != 0)    /* write data */
            {
                handle->debug_print("st7789: write data failed.\n");               /* write data failed */

                return 1;                                                          /* return error */
            }
        }
    }
    else
    {
        handle->debug_print("st7789: format is invalid.\n");                       /* format is invalid */

        return 4;                                                                  /* return error */
    }

    return 0;                                                                      /* success return 0 */
}

/**
 * @brief     draw a point in the display
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] color point color
 * @return    status code
 *            - 0 success
 *            - 1 draw point failed
 * @note      none
 */
static uint8_t a_st7789_draw_point(st7789_handle_t *handle, uint16_t x, uint16_t y, uint32_t color)
{
    uint8_t buf[4];

    if (a_st7789_write_byte(handle, ST7789_CMD_CASET, ST7789_CMD) != 0)            /* write set column address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (x >> 8) & 0xFF;                                                      /* start address msb */
    buf[1] = (x >> 0) & 0xFF;                                                      /* start address lsb */
    buf[2] = (x >> 8) & 0xFF;                                                      /* end address msb */
    buf[3] = (x >> 0) & 0xFF;                                                      /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RASET, ST7789_CMD) != 0)            /* write set row address command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }
    buf[0] = (y >> 8) & 0xFF;                                                      /* start address msb */
    buf[1] = (y >> 0) & 0xFF;                                                      /* start address lsb */
    buf[2] = (y >> 8) & 0xFF;                                                      /* end address msb */
    buf[3] = (y >> 0) & 0xFF;                                                      /* end address lsb */
    if (a_st7789_write_bytes(handle, buf, 4, ST7789_DATA) != 0)                    /* write data */
    {
        handle->debug_print("st7789: write data failed.\n");                       /* write data failed */

        return 1;                                                                  /* return error */
    }

    if (a_st7789_write_byte(handle, ST7789_CMD_RAMWR, ST7789_CMD) != 0)            /* write memory write command */
    {
        handle->debug_print("st7789: write command failed.\n");                    /* write command failed */

        return 1;                                                                  /* return error */
    }

    if ((handle->format & 0x03) == 0x03)                                           /* rgb444 */
    {
        handle->buf[0] = (((color >> 8) & 0xF) << 4) |
                         (((color >> 4) & 0xF) << 0);                              /* set the color */
        handle->buf[1] = (((color >> 0) & 0xF) << 4);                              /* set the color */
        if (a_st7789_write_bytes(handle, handle->buf,
            2, ST7789_DATA) != 0)                                                  /* write data */
        {
            handle->debug_print("st7789: write data failed.\n");                   /* write data failed */

            return 1;                                                              /* return error */
        }
    }
    else if ((handle->format & 0x05) == 0x05)                                      /* rgb565 */
    {
        handle->buf[0] = (color >> 8) & 0xFF;                                      /* set the color */
        handle->buf[1] = (color >> 0) & 0xFF;                                      /* set the color */
        if (a_st7789_write_bytes(handle, handle->buf,
            2, ST7789_DATA) != 0)                                                  /* write data */
        {
            handle->debug_print("st7789: write data failed.\n");                   /* write data failed */

            return 1;                                                              /* return error */
        }
    }
    else if ((handle->format & 0x06) == 0x06)                                      /* rgb666 */
    {
        handle->buf[0] = ((color >> 12) & 0x3F) << 2;                              /* set the color */
        handle->buf[1] = ((color >> 6) & 0x3F) << 2;                               /* set the color */
        handle->buf[2] = ((color >> 0) & 0x3F) << 2;                               /* set the color */
        if (a_st7789_write_bytes(handle, handle->buf,
            3, ST7789_DATA) != 0)                                                  /* write data */
        {
            handle->debug_print("st7789: write data failed.\n");                   /* write data failed */

            return 1;                                                              /* return error */
        }
    }
    else
    {
        handle->debug_print("st7789: format is invalid.\n");                       /* format is invalid */

        return 4;                                                                  /* return error */
    }

    return 0;                                                                      /* success return 0 */
}

/**
 * @brief     draw a char in the display
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] chr display char
 * @param[in] size display size
 * @param[in] color display color
 * @return    status code
 *            - 0 success
 *            - 1 show char failed
 * @note      none
 */
static uint8_t a_st7789_show_char(st7789_handle_t *handle, uint16_t x, uint16_t y, uint8_t chr, uint8_t size, uint32_t color)
{
    uint8_t temp, t, t1;
    uint16_t y0 = y;
    uint8_t csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);                 /* get size */

    chr = chr - ' ';                                                                /* get index */
    for (t = 0; t < csize; t++)                                                     /* write size */
    {
        if (size == 12)                                                             /* if size 12 */
        {
            temp = gsc_st7789_ascii_1206[chr][t];                                   /* get ascii 1206 */
        }
        else if (size == 16)                                                        /* if size 16 */
        {
            temp = gsc_st7789_ascii_1608[chr][t];                                   /* get ascii 1608 */
        }
        else if(size == 24)                                                         /* if size 24 */
        {
            temp = gsc_st7789_ascii_2412[chr][t];                                   /* get ascii 2412 */
        }
        else
        {
            return 1;                                                               /* return error */
        }
        for (t1 = 0; t1 < 8; t1++)                                                  /* write one line */
        {
            if ((temp & 0x80) != 0)                                                 /* if 1 */
            {
                if (a_st7789_draw_point(handle, x, y, color) != 0)                  /* draw point */
                {
                    return 1;                                                       /* return error */
                }
            }
            temp <<= 1;                                                             /* left shift 1 */
            y++;
            if ((y - y0) == size)                                                   /* reset size */
            {
                y = y0;                                                             /* set y */
                x++;                                                                /* x++ */

                break;                                                              /* break */
            }
        }
    }

    return 0;                                                                       /* success return 0 */
}

/**
 * @brief     write a string in the display
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] *str pointer to a write string address
 * @param[in] len length of the string
 * @param[in] color display color
 * @param[in] font string font
 * @return    status code
 *            - 0 success
 *            - 1 draw point failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 x or y is invalid
 * @note      x < column && y < row
 */
uint8_t st7789_write_string(st7789_handle_t *handle, uint16_t x, uint16_t y, char *str, uint16_t len, uint32_t color, st7789_font_t font)
{
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    if((x >= handle->column) || (y >= handle->row))                          /* check x, y */
    {
        handle->debug_print("ssd1351: x or y is invalid.\n");                /* x or y is invalid */

        return 4;                                                            /* return error */
    }

    while ((len != 0) && (*str <= '~') && (*str >= ' '))                     /* write all string */
    {
        if (x >= (handle->column - (font / 2)))                              /* check x point */
        {
            x = 0;                                                           /* set x */
            y += (uint8_t)font;                                              /* set next row */
        }
        if (y >= (handle->row - font))                                       /* check y pont */
        {
            y = x = 0;                                                       /* reset to 0 */
        }
        if (a_st7789_show_char(handle, x, y, *str, font, color) != 0)        /* show a char */
        {
            return 1;                                                        /* return error */
        }
        x += (uint8_t)(font / 2);                                            /* x + font/2 */
        str++;                                                               /* str address++ */
        len--;                                                               /* str length-- */
    }

    return 0;                                                                /* success return 0 */
}

/**
 * @brief     draw a point in the display
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] x coordinate x
 * @param[in] y coordinate y
 * @param[in] color point color
 * @return    status code
 *            - 0 success
 *            - 1 draw point failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 x is over column
 *            - 5 y is over row
 * @note      x < column && y < row
 */
uint8_t st7789_draw_point(st7789_handle_t *handle, uint16_t x, uint16_t y, uint32_t color)
{
    if (handle == NULL)                                          /* check handle */
    {
        return 2;                                                /* return error */
    }
    if (handle->inited != 1)                                     /* check handle initialization */
    {
        return 3;                                                /* return error */
    }
    if (x >= handle->column)                                     /* check x */
    {
        handle->debug_print("ssd1351: x is over column.\n");     /* x is over column */

        return 4;                                                /* return error */
    }
    if (y >= handle->row)                                        /* check y */
    {
        handle->debug_print("ssd1351: y is over row.\n");        /* y is over row */

        return 5;                                                /* return error */
    }

    return a_st7789_draw_point(handle, x, y, color);             /* draw point */
}

/**
 * @brief     write the command
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] cmd sent command
 * @return    status code
 *            - 0 success
 *            - 1 write command failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_write_cmd(st7789_handle_t *handle, uint8_t cmd)
{
    if (handle == NULL)                                         /* check handle */
    {
        return 2;                                               /* return error */
    }
    if (handle->inited != 1)                                    /* check handle initialization */
    {
        return 3;                                               /* return error */
    }

    return a_st7789_write_byte(handle, cmd, ST7789_CMD);        /* write command */
}

/**
 * @brief     write the data
 * @param[in] *handle pointer to an st7789 handle structure
 * @param[in] data sent data
 * @return    status code
 *            - 0 success
 *            - 1 write data failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t st7789_write_data(st7789_handle_t *handle, uint8_t data)
{
    if (handle == NULL)                                          /* check handle */
    {
        return 2;                                                /* return error */
    }
    if (handle->inited != 1)                                     /* check handle initialization */
    {
        return 3;                                                /* return error */
    }

    return a_st7789_write_byte(handle, data, ST7789_DATA);       /* write data */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an st7789 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t st7789_info(st7789_info_t *info)
{
    if (info == NULL)                                              /* check handle */
    {
        return 2;                                                  /* return error */
    }

    memset(info, 0, sizeof(st7789_info_t));                        /* initialize st7789 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                       /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);       /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;               /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;               /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                            /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                       /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                       /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                         /* set driver version */

    return 0;                                                      /* success return 0 */
}
