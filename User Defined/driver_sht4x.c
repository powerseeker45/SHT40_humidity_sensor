#include "driver_sht4x.h"
#include <string.h>

static uint8_t calculate_crc(uint8_t *data, uint16_t len)
{
    const uint8_t POLYNOMIAL = 0x31;  /* Polynomial for CRC-8 calculation */
    uint8_t crc = 0xFF;               /* Initial value for CRC */
  
    for (uint16_t j = 0; j < len; j++)  /* Loop through each byte in the data */
    {
        crc ^= data[j];                /* XOR current data byte with CRC */
        for (uint8_t i = 0; i < 8; i++) /* Process 8 bits of each byte */
        {
            if (crc & 0x80)            /* If the MSB is 1 */
            {
                crc = (crc << 1) ^ POLYNOMIAL; /* Shift left and XOR with polynomial */
            }
            else
            {
                crc <<= 1;             /* Just shift left if MSB is 0 */
            }
        }
    }
  
    return crc;  /* Return the calculated CRC value */
}

uint8_t sht4x_read(sht4x_handle_t *handle, sht4x_mode_t mode, 
                   uint16_t *temperature_raw, float *temperature_s, 
                   uint16_t *humidity_raw, float *humidity_s) 
{
    uint8_t buf[6];
    uint8_t command = (uint8_t)mode;

    if (handle == NULL || handle->i2c_handle == NULL) {
        return 2; /* Error: invalid handle */
    }

    /* Send command to SHT4x */
    if (HAL_I2C_Master_Transmit(handle->i2c_handle, 
                                (handle->i2c_address << 1), 
                                &command, 1, HAL_MAX_DELAY) != HAL_OK) {
        return 1; /* Error: I2C transmission failed */
    }

    /* Wait based on mode's measurement time */
    switch (mode) {
        case SHT4X_MODE_HIGH_PRECISION_WITH_NO_HEATER:
        case SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_200MW_1S:
        case SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_110MW_1S:
        case SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_20MW_1S:
            HAL_Delay(10); /* 10 ms delay */
            break;
        case SHT4X_MODE_MEDIUM_PRECISION_WITH_NO_HEATER:
            HAL_Delay(5); /* 5 ms delay */
            break;
        case SHT4X_MODE_LOWEST_PRECISION_WITH_NO_HEATER:
            HAL_Delay(2); /* 2 ms delay */
            break;
        case SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_200MW_0P1S:
        case SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_110MW_0P1S:
        case SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_20MW_0P1S:
            HAL_Delay(1); /* 1 ms delay */
            break;
        default:
            return 3; /* Error: invalid mode */
    }

    /* Read measurement data */
    if (HAL_I2C_Master_Receive(handle->i2c_handle, 
                               (handle->i2c_address << 1) | 1, 
                               buf, 6, HAL_MAX_DELAY) != HAL_OK) {
        return 1; /* Error: I2C reception failed */
    }

    if (calculate_crc(buf, 2) != buf[2]) {
        return 4; /* Error: CRC mismatch for temperature */
    }

    if (calculate_crc(buf + 3, 2) != buf[5]) {
        return 4; /* Error: CRC mismatch for humidity */
    }

    *temperature_raw = ((uint16_t)buf[0] << 8) | buf[1];
    *humidity_raw = ((uint16_t)buf[3] << 8) | buf[4];

    *temperature_s = (float)(*temperature_raw) / 65535.0f * 175.0f - 45.0f;
    *humidity_s = (float)(*humidity_raw) / 65535.0f * 125.0f - 6.0f;

    return 0; 
}

uint8_t sht4x_soft_reset(sht4x_handle_t *handle) {
    uint8_t command = 0x94; /* SHT4x soft reset command */

    if (handle == NULL || handle->i2c_handle == NULL) {
        return 2; /* Error: invalid handle */
    }

    if (HAL_I2C_Master_Transmit(handle->i2c_handle, 
                                (handle->i2c_address << 1), 
                                &command, 1, HAL_MAX_DELAY) != HAL_OK) {
        return 1;
    }

    HAL_Delay(1);

    return 0;
}
