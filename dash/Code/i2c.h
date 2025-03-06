// i2c.h
#ifndef I2C_H
#define I2C_H

#include <xc.h>
#include <stdint.h>

#define LCD_ADDRESS 0x20 // PCF8574 I2C address (A0, A1, A2 grounded)
#define SEG_ADDRESS 0x70 // HT16K33 I2C address default

// Function prototype
void i2c_init(void);
void i2c_send_byte(uint8_t data);
void i2c_start(void);
void i2c_stop(void);
void i2c_wait(void);

#endif