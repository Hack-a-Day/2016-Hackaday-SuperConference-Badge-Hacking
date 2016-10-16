/* 
 * File:   main.c
 * Author: szczys@hotmail.com
 *
 * This is a C framework for hacking the 2016 Hackaday SuperConference hardware badge.
 *
 * The badge uses a bootloader which is running a hardware handling "kernel". The methods to
 * access thesehardware features are in this file (main.c), the memory mapped values are in HaD_Badge.h
 *
 * User code should be placed in SuperCon-badge.animate.c, which is currently a set of examples
 * showing how to write to the display, use non-blocking delays, read buttons, and access the accelerometer.
 * 
 * Bootloader mode is entered by connecting USB to computer and holding Power while pressing Reset
 *   Badge will appear on computer as a USB storage device. Copy .hex file to badge, press power to run user code.
 *
 * MIT License (see license.txt)
 * Copyright (c) 2016 Hackaday.com
 */

#include <stdio.h>
#include <stdlib.h>
#include "HaD_Badge.h"
#include "SuperCon-badge-animate.h"

volatile uint16_t innerTick = 0;
volatile uint32_t ticks = 0;


void interrupt high_priority interrupt_at_high_vector(void)
{
    //NOTE: Timer0 and Timer2 are in use by the bootloader/kernel
    
    /***** User Code for high priority interrupts *****/
    if (TMR0IF) {
        //This overflow used by the display scanning (1202Hz)
        ++ticks;        //Increment time variable (~20 days to overflow)
    }
    /***** End User Code for high priority interrupts *****/
    
    //this ASM call must end the function (needed for kernel compliance)
    asm("goto 0x2B08");
}

// LOW VECTOR

//#pragma code low_vector=0x1806
void interrupt low_priority interrupt_at_low_vector(void)
{   
    /***** User Code for low priority interrupts *****/
    
    /***** End User Code for low priority interrupts *****/
    
    //this ASM call must end the function (needed for kernel compliance)
    asm("goto 0x2B18");
}

/*****End Kernel Compliance Section********************************************/

/*****Software Emulator Compliance Functions***********************************/
/*---- Display Functions ----*/
void initDisplay(void) {
    //Turn on display and set all LEDs off   
    /* Do Nothing -- Handled by kernel */
    /* function still needed for emulator compliance */
}
void displayClear(void) {
    //Turn all LEDs off
    for (uint8_t i=0; i<16; i++) {
        Buffer[i] = 0x00;
    }
}

void displayPixel(uint8_t x, uint8_t y, uint8_t state) {
    //Set LED to state (ON|OFF)
    uint8_t mask = 1<<(7-x);
    if (state == ON) {
        Buffer[y] |= mask;
    }
    else {
        Buffer[y] &= ~(mask);
    }
}

void displayClose(void) {
    //Close the display (used for SDL2 emulator window)
    /* Do nothing, not used on hardware badge*/
    /* function still needed for emulator compliance */
}
void displayLatch(void) {
    //Make display changes visible (can be used for a framebuffer)
    /* Do nothing, not used on hardware badge*/
    /* function still needed for emulator compliance */
}
/*--------------------*/



/*---- Control Functions ----*/
void initControl(void) {
    //Setup button input
    /* Do nothing, not used on hardware badge*/
    /* function still needed for emulator compliance */
}

uint8_t getControl(void) {
    //Return last pressed button
    uint8_t key_mask = KeyEdge;
    //Remember to reset KeyEdge after reading
    KeyEdge = 0x00;
    if (key_mask & 1<<1) { return LEFT; }
    if (key_mask & 1<<4) { return RIGHT; }
    if (key_mask & 1<<2) { return UP; }
    if (key_mask & 1<<3) { return DOWN; }
    return 0;
}

void pollAccel(void) {
    // Tell the kernel to get data from the Accelerometer
    // After this function returns, data is in these variables:
         
        // AccXhigh and AccXlow (rotate left is lower, right higher)
        // AccYhigh and AccYlow (nose down is lower, up is higher)
        // AccZhigh and AccZlow (face down is lower, up is higher)
        
    // Each variable is 16-bits (high byte then low byte), with only the
    // 11 most significant bits containing data.
    
    asm("goto 0x2B14"); //Function address for kernel accelerometer read
}

uint32_t getTime(void) {
    //Return approximate milliseconds (upcounting)
    
    //We're actually incrementing at 1202Hz so
    //some magic will be used here to normalize to milliseconds
    //This should be somewhat fast using shifting to approximate a weird division
    // 50%+25%=75%  (need 83.19% so about 9.84% error but some time is wasted with other stuff -- close enough for user)
    
    return (ticks>>1)+(ticks>>2);
}

void controlDelayMs(uint16_t ms) {
    //Delay milliseconds (blocking)
    
    ms = ms/10;
    while (ms > 0) {
        __delay_ms(10);
        --ms;
    }
}

/*****End Software Emulator Compliance*****************************************/

/*
 * For software emulator compliance main must call animateBadge()
 */
int main(int argc, char** argv) {
    /****Functions must be called to place code for kernel****/
    //initBootloaderInterruptHandling();
    /****End mandatory function calls*************************/
    
    /****Begin User Code**************************************/
    controlDelayMs(1);  //Just to get around "never called" compiler warning
    initDisplay();
    initControl();
    displayClear();
    displayLatch();
    getTime();
    
    animateBadge();
    
    return (EXIT_SUCCESS);
}
