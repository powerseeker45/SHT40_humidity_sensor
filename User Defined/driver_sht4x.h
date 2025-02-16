#ifndef SHT4X_H
#define SHT4X_H

#include "stm32h7xx_hal.h"
#include <stdint.h>

/* SHT4x operation modes */
typedef enum {
    SHT4X_MODE_HIGH_PRECISION_WITH_NO_HEATER = 0xFD,
    SHT4X_MODE_MEDIUM_PRECISION_WITH_NO_HEATER = 0xF6,
    SHT4X_MODE_LOWEST_PRECISION_WITH_NO_HEATER = 0xE0,
    SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_200MW_1S = 0x39,
    SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_200MW_0P1S = 0x32,
    SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_110MW_1S = 0x2F,
    SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_110MW_0P1S = 0x24,
    SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_20MW_1S = 0x1E,
    SHT4X_MODE_HIGH_PRECISION_WITH_HEATER_20MW_0P1S = 0x15,
} sht4x_mode_t;

/* SHT4x handle structure */
typedef struct {
    I2C_HandleTypeDef *i2c_handle;  /* I2C handle */
    uint8_t i2c_address;           /* SHT4x I2C address (default 0x44 or 0x45) */
} sht4x_handle_t;

/* Function prototypes */
uint8_t sht4x_read(sht4x_handle_t *handle, sht4x_mode_t mode, 
                   uint16_t *temperature_raw, float *temperature_s, 
                   uint16_t *humidity_raw, float *humidity_s);
static uint8_t calculate_crc(uint8_t *data, uint16_t len);

#endif /* SHT4X_H */
