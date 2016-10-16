/* 
 * File:   SuperCon-badge-animate.h
 * Author: szczys@hotmail.com
 *
 * MIT License (see license.txt)
 * Copyright (c) 2016 Hackaday.com
 */
 
#ifndef SUPERCON-BADGE-ANIMATE_H
#define	SUPERCON-BADGE-ANIMATE_H

 #include "HaD_Badge.h"

//Add your function protopes:
void eraseBall(void);
void moveLeft(void);
void moveRight(void);
void moveUp(void);
void moveDown(void);
void drawArrow(uint8_t rightOrLeft);

//This function prototype needs to be here:
void animateBadge(void);

#endif	/* SUPERCON-BADGE-ANIMATE_H */
