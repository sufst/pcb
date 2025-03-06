// lcd.c
#include "lcd.h"

static void lcd_delay_ms(uint16_t ms) {
    while (ms--) {
        __delay_ms(1);
    }
}

static void lcd_send_nibble(uint8_t data) {
    uint8_t data_high = (data << 4);  // No backlight bit, P3 is always high
    
    i2c_start();
    i2c_send_byte((LCD_ADDRESS << 1) | 0);
    i2c_send_byte(data_high | LCD_EN);
    i2c_send_byte(data_high & ~LCD_EN);
    i2c_stop();
    __delay_us(50);
}

static void lcd_send_byte(uint8_t data, uint8_t rs) {       // rs 1 for data register, rs 0 for command register
    uint8_t data_high = (data & 0xF0) | (rs ? LCD_RS : 0);
    uint8_t data_low = ((data << 4) & 0xF0) | (rs ? LCD_RS : 0);
    
    i2c_start();
    i2c_send_byte((LCD_ADDRESS << 1) | 0);
    i2c_send_byte(data_high | LCD_EN);
    __delay_us(1);
    i2c_send_byte(data_high & ~LCD_EN);
    __delay_us(50);
    
    i2c_send_byte(data_low | LCD_EN);
    __delay_us(1);
    i2c_send_byte(data_low & ~LCD_EN);
    i2c_stop();
    __delay_us(50);
}


//need to double check init protocol

void lcd_init(void) {
    lcd_delay_ms(50);
    lcd_send_nibble(0x03);  // Initialization sequence uses nibbles
    lcd_delay_ms(5);
    lcd_send_nibble(0x03);
    __delay_us(150);
    lcd_send_nibble(0x03);
    lcd_send_nibble(0x02);
    
    lcd_send_byte(LCD_FUNCTION_SET_2LINE, 0);  // RS = 0 for command
    lcd_send_byte(LCD_DISP_ON_CURSOR_OFF, 0);  // RS = 0 for command
    lcd_send_byte(LCD_CLEAR, 0);                // RS = 0 for command
    lcd_send_byte(LCD_INC_CURSOR, 0);           // RS = 0 for command
}

void lcd_clear(void) {
    lcd_send_byte(LCD_CLEAR, 0);  // RS = 0 for command
    lcd_delay_ms(2);
}

void lcd_home(void) {
    lcd_send_byte(LCD_HOME, 0);  // RS = 0 for command
    lcd_delay_ms(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? LCD_FORCE_CURSOR_LINE1 : LCD_FORCE_CURSOR_LINE2;
    address += col;
    lcd_send_byte(address, 0);  // RS = 0 for command
}

void lcd_write_char(char c) {
    lcd_send_byte(c, 1);  // RS = 1 for data
}

void lcd_write_string(const char *str) {
    while (*str) {
        lcd_send_byte(*str++, 1);  // RS = 1 for data
    }
}

void lcd_shift_cursor_left(void) {
    lcd_send_byte(LCD_SHIFT_CURSOR_LEFT, 0);  // RS = 0 for command
}

void lcd_shift_cursor_right(void) {
    lcd_send_byte(LCD_SHIFT_CURSOR_RIGHT, 0);  // RS = 0 for command
}

void lcd_shift_display_left(void) {
    lcd_send_byte(LCD_SHIFT_DISP_LEFT, 0);  // RS = 0 for command
}

void lcd_shift_display_right(void) {
    lcd_send_byte(LCD_SHIFT_DISP_RIGHT, 0);  // RS = 0 for command
}

void lcd_display_off_cursor_off(void) {
    lcd_send_byte(LCD_DISP_OFF_CURSOR_OFF, 0);  // RS = 0 for command
}

void lcd_display_off_cursor_on(void) {
    lcd_send_byte(LCD_DISP_OFF_CURSOR_ON, 0);  // RS = 0 for command
}

void lcd_display_on_cursor_off(void) {
    lcd_send_byte(LCD_DISP_ON_CURSOR_OFF, 0);  // RS = 0 for command
}

void lcd_display_on_cursor_blink(void) {
    lcd_send_byte(LCD_DISP_ON_CURSOR_BLINK, 0);  // RS = 0 for command
}