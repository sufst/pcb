// main.c
#include "i2c.h"
#include "lcd.h"
#include "seg.h"

// Function to delay for a specified number of seconds
void delay_seconds(uint16_t seconds) {
    while (seconds--) {
        __delay_ms(1000);
    }
}

int main(void) {
    // Configure the oscillator (HFINTOSC at 4 MHz as per OSCFRQ = 0x02)
    OSCCON1 = 0x60;  // Use HFINTOSC with divider
    OSCFRQ = 0x02;   // HFINTOSC frequency = 4 MHz
    
    // Initialize I2C, LCD, and 7-segment display
    i2c_init();
    lcd_init();
    seg_init();
    
    // Initial LCD setup: Display welcome message
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_write_string("Welcome!");
    lcd_set_cursor(1, 0);
    lcd_write_string("PIC18F47Q84");
    delay_seconds(2);
    
    // Initial 7-segment display: Show "00"
    seg_clear();
    seg_display_digits(0);
    delay_seconds(1);
    
    // Demo 1: Show whole numbers on 7-segment (0-99)
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_write_string("Counting:");
    for (uint8_t i = 0; i <= 99; i++) {
        lcd_set_cursor(1, 0);
        lcd_write_string("Value: ");
        lcd_write_char('0' + (i / 10));  // Tens digit
        lcd_write_char('0' + (i % 10));  // Units digit
        lcd_write_string("   ");  // Clear remaining characters
        
        seg_display_digits(i);
        __delay_ms(200);  // Update every 200ms for visibility
    }
    delay_seconds(1);
    
    // Demo 2: Show decimal numbers (e.g., 4.5, 2.1)
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_write_string("Decimals:");
    
    // Show 4.5
    lcd_set_cursor(1, 0);
    lcd_write_string("Value: 4.5");
    seg_display_digits(45);  // Show 4 and 5
    seg_display_dp(1, 1);    // Decimal point after first digit
    delay_seconds(2);
    
    // Show 2.1
    lcd_set_cursor(1, 0);
    lcd_write_string("Value: 2.1");
    seg_display_digits(21);  // Show 2 and 1
    seg_display_dp(1, 1);    // Decimal point after first digit
    delay_seconds(2);
    
    // Demo 3: Cursor and display shift on LCD with 7-segment
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_write_string("Shifting:");
    lcd_set_cursor(1, 0);
    lcd_write_string("Value: 42");
    seg_display_digits(42);
    
    // Shift LCD display and update 7-segment
    for (uint8_t i = 0; i < 5; i++) {
        lcd_shift_display_left();
        seg_display_digits(42 - i);  // Decrement from 42 to 37
        delay_seconds(1);
    }
    for (uint8_t i = 0; i < 5; i++) {
        lcd_shift_display_right();
        seg_display_digits(37 + i);  // Increment back to 42
        delay_seconds(1);
    }
    
    // Main loop: Cycle numbers with cursor blinking
    lcd_clear();
    lcd_set_cursor(0, 0);
    lcd_write_string("Cycle Mode:");
    while (1) {
        static uint8_t value = 0;
        
        // Update LCD with current value
        lcd_set_cursor(1, 0);
        lcd_write_string("Value: ");
        lcd_write_char('0' + (value / 10));
        lcd_write_char('0' + (value % 10));
        lcd_write_string("   ");
        
        // Update 7-segment display
        seg_display_digits(value);
        
        // Toggle cursor blinking
        lcd_display_on_cursor_blink();
        delay_seconds(1);
        lcd_display_on_cursor_off();
        delay_seconds(1);
        
        // Increment value
        value = (value + 1) % 100;
    }
    
    return 0;
}