// i2c.c
#include "i2c.h"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



need to change baud rate and clock configuration

need to fix errors for registers - verify actual names

need to double check init protocol

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


// Initialize I2C1 module
void i2c_init(void) {
    // Configure I2C1 pins (RC4 = SDA, RC3 = SCL on PIC18F47Q84)
    TRISCbits.TRISC4 = 1;  // SDA as input
    TRISCbits.TRISC3 = 1;  // SCL as input
    
    // Configure I2C1 for Master Mode
    I2C1CON0 = 0x00;       // Clear control register
    I2C1CON1 = 0x00;       // Clear control register
    I2C1CON2 = 0x00;       // Clear control register
    
    // Set baud rate for 100kHz @ 4MHz Fosc
    I2C1CLK = 0x09;        // (Fosc/(4 * BaudRate)) - 1 = (4MHz/(4 * 100kHz)) - 1
    
    // Enable I2C1
    I2C1CON0bits.EN = 1;
}

// Send data byte over I2C
void i2c_send_byte(uint8_t data) {
    I2C1TXB = data;        // Load data into transmit buffer
    while (!I2C1STAT0bits.TXBE);  // Wait for transmit buffer empty
}

// Start I2C transmission
void i2c_start(void) {
    while (I2C1STAT1bits.BUF);  // Wait if bus is busy
    I2C1CON0bits.S = 1;    // Generate Start condition
    while (!I2C1STAT0bits.S);  // Wait for Start condition to complete
}

// Stop I2C transmission
void i2c_stop(void) {
    while (I2C1STAT1bits.BUF);  // Wait if bus is busy
    I2C1CON0bits.P = 1;    // Generate Stop condition
    while (I2C1STAT0bits.P);   // Wait for Stop condition to complete
}

// Wait for I2C operation to complete
void i2c_wait(void) {
    while (I2C1STAT1bits.BUF);  // Wait for bus to be free
}