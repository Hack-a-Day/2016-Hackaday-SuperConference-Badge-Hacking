/* 
 * File:   SuperCon-badge-animate.c
 * Author: szczys@hotmail.com
 *
 * User code should be placed in this file. Follow the examples below:
 *   Write to display through Buffer[] and call displayLatch() to show changes on badge
 *   use getTime() for upcounting (approximate) milliseconds for non-blocking delays
 *   call getControl() to return a key mask of debounced button presses
 *   call pollAccel() to populate accelerometer data and read AccX(high/low), AccY(high/low), AccZ(high/low)
 *
 * MIT License (see license.txt)
 * Copyright (c) 2016 Hackaday.com
 */

#include "HaD_Badge.h"

uint8_t ballX = 4;
uint8_t ballY = 3;

//Hint: look in HaD_Badge.h for function and constant definitions

void eraseBall() {
    //uses global variables to erase current ball
    displayPixel(ballX, ballY, OFF);
    displayLatch();
}

void moveLeft() {
    if (ballX > 0) {
        //only move if we're not already at the edge
        eraseBall();
        --ballX;
        displayPixel(ballX, ballY, ON);
        displayLatch();
    }
}

void moveRight() {
    if (ballX < TOTPIXELX-1) {
        //only move if we're not already at the edge
        eraseBall();
        ++ballX;
        displayPixel(ballX, ballY, ON);
        displayLatch();
    }
}

void moveUp() {
    if (ballY > 0) {
        //only move if we're not already at the edge
        eraseBall();
        --ballY;
        displayPixel(ballX, ballY, ON);
        displayLatch();
    }
}

void moveDown() {
    //Limit ball travel to top 8 rows of the screen
    if (ballY < TOTPIXELY-9) {
        //only move if we're not already at the edge
        eraseBall();
        ++ballY;
        displayPixel(ballX, ballY, ON);
        displayLatch();
    }
}

void drawArrow(uint8_t rightOrLeft) {
    //0 == right
    //1 == left
    if (rightOrLeft) {
        Buffer[11] = 0b00100000;
        Buffer[12] = 0b01000000;
        Buffer[13] = 0b11111111;
        Buffer[14] = 0b01000000;
        Buffer[15] = 0b00100000;
    }
    else {
        Buffer[11] = 0b00000100;
        Buffer[12] = 0b00000010;
        Buffer[13] = 0b11111111;
        Buffer[14] = 0b00000010;
        Buffer[15] = 0b00000100;
    }
    displayLatch();
}

void animateBadge(void) {
    displayPixel(ballX, ballY, ON);
    displayLatch();
    uint32_t nextTime = getTime();

    while(1) {
        
        //This shows how to use non-blocking getTime() function
        if (getTime() > nextTime) {
            nextTime = getTime()+1000;  //prepare next event for about 1000ms (1 second) from now
            Buffer[8] ^= 0xFF;  //Toggle a whole row
            Buffer[9] ^= 0xFF;  //Toggle a whole row
            displayLatch();     //Make sure changes to the buffer show up on the display
        }

        //Use accelerometer to draw left or right arrow for X axis
        pollAccel();    //Tell kernel to read the accelerometer values
        if (AccXhigh < 0xF0) { drawArrow(1); } //Use high 8-bits of X value to decide what to do.
        else { drawArrow(0); }
        
        //This shows how to get user input
        switch (getControl()) {
            case (ESCAPE):
                displayClose();
                return;
            case (LEFT):
                moveLeft();
                break;
            case (RIGHT):
                moveRight();
                break;
            case (UP):
                moveUp();
                break;
            case (DOWN):
                moveDown();
                break;
        }
    }
}