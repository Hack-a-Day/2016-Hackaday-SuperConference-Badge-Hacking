/* 
 * File:   HaD_Badge.h
 * Author: szczys@hotmail.com
 *
 * Prototypes for hardware control functions and memory map for kernel values
 *
 * MIT License (see license.txt)
 * Copyright (c) 2016 Hackaday.com
 */

#ifndef HAD_BADGE_H
#define	HAD_BADGE_H

#include <stdint.h>
#include <xc.h>

#define _XTAL_FREQ 48000000

#define TOTPIXELX       8
#define TOTPIXELY       16

//LED Control definitions
#define OFF     0
#define ON      1

//Directions of travel
#define UP      2
#define DOWN    3
#define LEFT    1
#define RIGHT   4
//Miscellaneous
#define ESCAPE  5
#define NOINPUT 6
#define BUTTON  7
    
/*---- Display Prototypes ----*/
void initDisplay(void);             //Turn on display and set all LEDs off
void displayClear(void);            //Turn all LEDs off
void displayPixel(uint8_t x, uint8_t y, uint8_t state); //Set LED to state (ON|OFF)
void displayClose(void);            //Close the display (used for SDL2 emulator window)
void displayLatch(void);            //Make display changes visible (can be used for a framebuffer)
/*--------------------*/



/*---- Control Prototypes ----*/
void initControl(void);             //Setup button input
uint8_t getControl(void);           //Return last pressed button
uint32_t getTime(void);             //Return approximate milliseconds (upcounting)
void pollAccel(void);               //Make kernel copy accelerometer values to AccX, AccY, AccZ
void controlDelayMs(uint16_t ms);   //Delay milliseconds (blocking)
/*---- Bootloader Interrupt Vector Handling ---*/
void interrupt high_priority interrupt_at_high_vector(void);
void interrupt low_priority interrupt_at_low_vector(void);

/*---- Config bits must match what is used by bootloader/kernel ----*/
// CONFIG1L
#pragma config PLLSEL = PLL3X   // PLL Selection (3x clock multiplier)
#pragma config CFGPLLEN = ON    // PLL Enable Configuration bit (PLL Enabled)
#pragma config CPUDIV = NOCLKDIV// CPU System Clock Postscaler (CPU uses system clock (no divide))
#pragma config LS48MHZ = SYS48X8// Low Speed USB mode with 48 MHz system clock (System clock at 48 MHz, USB clock divider is set to 8)

// CONFIG1H
#pragma config FOSC = INTOSCIO  // Oscillator Selection (Internal oscillator)
#pragma config PCLKEN = OFF     // Primary Oscillator Shutdown (Primary oscillator shutdown firmware controlled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config nPWRTEN = OFF    // Power-up Timer Enable (Power up timer disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (BOR disabled in hardware (SBOREN is ignored))
#pragma config BORV = 190       // Brown-out Reset Voltage (BOR set to 1.9V nominal)
#pragma config nLPBOR = OFF     // Low-Power Brown-out Reset (Low-Power Brown-out Reset disabled)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (WDT disabled in hardware (SWDTEN ignored))
#pragma config WDTPS = 32768    // Watchdog Timer Postscaler (1:32768)

// CONFIG3H
#pragma config CCP2MX = RC1     // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config T3CMX = RC0      // Timer3 Clock Input MUX bit (T3CKI function is on RC0)
#pragma config SDOMX = RB3      // SDO Output MUX bit (SDO function is on RB3)
#pragma config MCLRE = ON       // Master Clear Reset Pin Enable (MCLR pin enabled; RE3 input disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Block 0 Code Protect (Block 0 is not code-protected)
#pragma config CP1 = OFF        // Block 1 Code Protect (Block 1 is not code-protected)
#pragma config CP2 = OFF        // Block 2 Code Protect (Block 2 is not code-protected)
#pragma config CP3 = OFF        // Block 3 Code Protect (Block 3 is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protect (Boot block is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protect (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Block 0 Write Protect (Block 0 (0800-1FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Block 1 Write Protect (Block 1 (2000-3FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Block 2 Write Protect (Block 2 (04000-5FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Block 3 Write Protect (Block 3 (06000-7FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Registers Write Protect (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protect (Boot block (0000-7FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protect (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Block 0 Table Read Protect (Block 0 is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Block 1 Table Read Protect (Block 1 is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Block 2 Table Read Protect (Block 2 is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Block 3 Table Read Protect (Block 3 is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protect (Boot block is not protected from table reads executed in other blocks)
/*---- End Config bits ----*/

/****************Memory Map***********************/
volatile uint8_t KeyEdge    @ 0x00;     //KeyEdge 0 = set by kernel; //if key INT edge detected(user must reset)
volatile uint8_t Rotor0     @ 0x01;     //Rotor0 Used for key INT debouncer(bit 0 = 0 if key pressed)
volatile uint8_t Rotor1     @ 0x02;     //Rotor1 Used for key LEFT debouncer(bit 0 = 0 if key pressed)
volatile uint8_t Rotor2     @ 0x03;     //Rotor2 Used for key UP debouncer(bit 0 = 0 if key pressed)
volatile uint8_t Rotor3     @ 0x04;     //Rotor3 Used for key DOWN debouncer(bit 0 = 0 if key pressed)
volatile uint8_t Rotor4     @ 0x05;     //Rotor4 Used for key RIGHT debouncer(bit 0 = 0 if key pressed)
volatile uint8_t Flag       @ 0x06;     //Flag 0 = set by kernel : Pause, clr by kernel : Run mode(read only)
volatile uint8_t RXFlag     @ 0x07;     //RXFlag 0 = set : Enable auto RX to RAM 0x600...0x6FF and to EEprom
volatile uint8_t Brightness @ 0x08;     //Brightness Display ON PWM, user presets to 0...15 for dimming
volatile uint8_t GPreg      @ 0x09;     //GPreg General purpose register, may be used by user
volatile uint8_t AnodeCount	@ 0x0A;     //display multiplex counter 0...7
volatile uint8_t BitMask    @ 0x0B;     //BitMask 10000000...00000001, shift reg(CA) or 0...7 row count(CC)
volatile uint8_t T0period   @ 0x0C;     //T0period Total Timer 0 period, may be modified to alter scan frequency
volatile uint8_t InnerInt   @ 0x0D;     //InnerInt Loop counter, used by interrupt routine
volatile uint8_t OuterInt   @ 0x0E;     //OuterInt Loop counter, used by interrupt routine
volatile uint8_t OuterPlusInt @ 0x0F;   //OuterPlusInt Loop counter, used by interrupt routine
volatile uint8_t RXptr      @ 0x10;     //RXptr Low RXD buffer pointer(high is always = 6)
volatile uint8_t RXpatience @ 0x11;     //RXpatience Patience counter, preset when byte received, count down
volatile uint8_t PowerOFF   @ 0x12;     //PowerOFF Auto Power Off period(×6 sec), preset here to alter timing
volatile uint8_t PowerCount @ 0x13;     //PowerCount Auto Power Off count down
volatile uint8_t Inner @ 0x14;          //inner loop counter (used outside int routine)
volatile uint8_t Outer @ 0x15;          //outer loop counter (used outside int routine)
volatile uint16_t Uniform   @ 0x16;     //Uniform(2 bytes) 150 Hz divider, count up for 6 sec timing
volatile uint16_t RXserial  @ 0x18;     //RXserial(2 bytes) Received serial number(binary), ready for comparison
volatile uint16_t MySerial  @ 0x1A;     //MySerial(2 bytes) unit serial number copied from ROM address 0x100E
volatile uint16_t FSR0temp  @ 0x1C;     //FSR0temp(2 bytes) Temporary FSR0 during INT
volatile uint8_t AccXlow @ 0x1E;          //Accelerometer X	(keep order!)
volatile uint8_t AccXhigh @ 0x1F;
volatile uint16_t AccYlow @ 0x20;          //Accelerometer Y	(keep order!)
volatile uint8_t AccYhigh @ 0x21;
volatile uint16_t AccZlow @ 0x22;          //Accelerometer Z	(keep order!)
volatile uint8_t AccZhigh @ 0x23;
/*******************   0x1C...0x5FF User data RAM space ***********************/
volatile uint8_t RXBuffer[256]  @ 0x600;//0x600...0x6FF RX Buffer, used by infrared port routine(bytes loaded here)
volatile uint8_t Buffer[16]     @ 0x700;//0x700...0x70F Display buffer, upper row first, bit 7 = left column(user writes here)
volatile uint8_t AuxBuffer[16]  @ 0x710;//0x710...0x71F Aux buffer(not displayed by interrupt display refresh, used by user)
volatile uint8_t Pause[16]      @ 0x720;//0x720...0x72F Pause display buffer(displayed only during pause)
volatile uint32_t RNDseed   @ 0x730;    //0x730...0x733 RND seed *
volatile uint32_t RND       @ 0x734;    //0x734...0x737 RND internal arithmetic registers

#endif	/* HAD_BADGE_H */
