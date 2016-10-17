2016 Hackaday SuperConference Badge Hacking Template
====================================================

![2016 SuperCon Badge Front and Back](https://hackadaycom.files.wordpress.com/2016/10/both.jpg)

This is C framework to make hacking [the SuperCon](https://hackaday.io/superconference) badge easy.

[Full documentation for this badge](https://hackaday.io/project/16401-supercon-ii-badge) is up on Hackaday.io. There is a 'kernel' running in protected
bootloader space which services all of the hardware (display scanning, button debounce, etc.).
This project contains the functions and memory map to utilize the kernel functions.

View these funcitons and memory mapping in main.c and HaD_badge.h

Use code should be placed in SuperCon-badge-animate.c (and .h). These user files
currently contain examples of the following:

*  How to write to the display
*  How to take user button input
*  How to use non-blocking delays
*  How to access the accelerometer

## Entering bootloader mode and program badge

*  Connect the badge to your computer via USB
*  Hold the power button and press reset. The badge will appear on your computer as a USB storage device
*  Copy your compiled .hex file to this drive
*  Press the power button to begin running the newly flashed program

## More Information

This program file is an MPLAB X project. Download the IDE and compiler here:

*  [Microchip MPLAB X IDE](http://microchip.wikidot.com/mplabx:installation)
*  [Microchip XC8 Compiler](http://microchip.wikidot.com/xc8:installation) (v1.38 known working)

Alternatively you can use the online version, [MPLAB Xpress](https://mplabxpress.microchip.com/mplabcloud/ide), without the need to install anything.

*  [Go here](https://mplabxpress.microchip.com/mplabcloud/Example/Details/259#) to open in Online IDE (click Open in IDE button when you get there)

Use the "Make and Program Device" button of Xpress to download your compiled .hex file.

## Schematic

![2016 SuperCon Badge schematic](https://hackadaycom.files.wordpress.com/2016/10/schematic-2016-supercon-badge.jpeg)
