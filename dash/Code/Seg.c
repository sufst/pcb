// seg.c
#include "seg.h"

// Lookup table for 7-segment patterns (0-9, common cathode)
static const uint8_t seg_patterns[] = {
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,      // 0
    SEG_B | SEG_C,                                     // 1
    SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,             // 2
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,             // 3
    SEG_B | SEG_C | SEG_F | SEG_G,                     // 4
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,             // 5
    SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,     // 6
    SEG_A | SEG_B | SEG_C | SEG_F,                             // 7
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, // 8
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G      // 9
};

// Buffer to hold display data (4 bytes for 2 digits, 2 bytes per digit)
static uint8_t display_buffer[4] = {0};

static void seg_send_command(uint8_t command) {
    i2c_start();
    i2c_send_byte((SEG_ADDRESS << 1) | 0);  // Write address (0xE0 for 0x70)
    i2c_send_byte(command);
    i2c_stop();
}

static void seg_write_display(void) {
    i2c_start();
    i2c_send_byte((SEG_ADDRESS << 1) | 0);  // Write address
    i2c_send_byte(0x00);  // Start at address 0x00 (display RAM)
    for (uint8_t i = 0; i < 4; i++) {
        i2c_send_byte(display_buffer[i]);
    }
    i2c_stop();
}

void seg_init(void) {
    i2c_init();
    __delay_ms(50);  // Wait for HT16K33 to power up
    
    // Initialize HT16K33
    seg_send_command(HT16K33_OSCILLATOR_ON);  // Turn on oscillator
    seg_send_command(HT16K33_DISPLAY_ON);     // Turn on display, no blinking
    seg_send_command(0xEF);                   // Set maximum brightness (0xE0 | 0x0F)
    seg_clear();
}

void seg_display_digits(uint8_t value) {
    if (value > 99) value = 99;  // Clamp value to 0-99
    
    uint8_t tens = value / 10;   // Extract tens digit (e.g., 99 → 9, 21 → 2)
    uint8_t units = value % 10;  // Extract units digit (e.g., 99 → 9, 21 → 1)
    
    // Set first digit (tens, position 0)
    display_buffer[0] = 0x00;  // Clear upper byte
    display_buffer[1] = seg_patterns[tens];  // Set segment pattern for tens
    
    // Set second digit (units, position 1)
    display_buffer[2] = 0x00;  // Clear upper byte
    display_buffer[3] = seg_patterns[units];  // Set segment pattern for units
    
    seg_write_display();
}

void seg_display_dp(uint8_t position, uint8_t state) {
    if (position < 2) {  // Only positions 0-1 for 2 digits
        uint8_t offset = position * 2 + 1;
        if (state) {
            display_buffer[offset] |= SEG_DP;  // Turn on decimal point
        } else {
            display_buffer[offset] &= ~SEG_DP;  // Turn off decimal point
        }
        seg_write_display();
    }
}

void seg_clear(void) {
    for (uint8_t i = 0; i < 4; i++) {
        display_buffer[i] = 0x00;
    }
    seg_write_display();
}