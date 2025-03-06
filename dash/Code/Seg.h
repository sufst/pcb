// seg.h
#ifndef SEG_H
#define SEG_H

#include "i2c.h"
#include <stdint.h>

// Define 7-segment display patterns (common cathode, adjust for common anode if needed)
#define SEG_A 0x01
#define SEG_B 0x02
#define SEG_C 0x04
#define SEG_D 0x08
#define SEG_E 0x10
#define SEG_F 0x20
#define SEG_G 0x40
#define SEG_DP 0x80  // Decimal point

// HT16K33 Command Definitions
#define HT16K33_OSCILLATOR_ON  0x21  // Turn on oscillator
#define HT16K33_DISPLAY_ON     0x81  // Display on, no blinking
#define HT16K33_DISPLAY_OFF     0x80  // Display off

// Function prototypes
void seg_init(void);
void seg_display_digits(uint8_t value);  // Display digit 0-9 at position 0-1
void seg_display_dp(uint8_t position, uint8_t state);    // Turn decimal point on/off at position
void seg_clear(void);

#endif