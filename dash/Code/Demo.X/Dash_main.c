#include <xc.h> //PIC Compiler
#include <pic18f47q84.h> // MCU
#include <stdio.h> // For sprintf
#include <stdint.h>

//Define oscillator frequency for delay functions (if used)
#define _XTAL_FREQ 64000000

//Structure to hold a CAN recieve message
typedef struct {
    uint16_t id;     // Standard 11-bit ID (assuming CAN 2.0 standard frames)
    uint8_t dlc;     // Data length code (0-8 for CAN 2.0)
    uint8_t data[8]; // Data bytes (up to 8 bytes)
} CANMessage;

//Function prototypes
void System_Init();
void CAN_Init();
uint8_t CAN_Recieve(CANMessage *msg);
void I2C_Init();
void LCD_Write(char* text);
void SEG_Write(uint8_t* digits);

void main(void) {
    System_Init(); // Configure system
    CAN_Init(); //Initialise CAN module
    I2C_Init(); //Initialise I2C module
    
    char lcd_buffer[16]; //Buffer for LCD (16 chars per line)
    uint8_t seg_buffer[4]; //Buffer for 7-segment display

    while(1) {
        CANMessage msg;

        if ()
    }
}

void System_Init() {
    //Configure PIC18F47q84
}

void CAN_Init() {
    //Configure necessary register bits for CAN communication
}

uint8_t CAN_Recieve(CANMessage *msg) {

}

void I2C_Init() {

}