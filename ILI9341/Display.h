/*
 * Display.h
 *
 *  Created on: 09.03.2019
 *      Author: KB1992pl
 *      https://github.com/KB1992pl/
The MIT License

Copyright (c) 2019 Kamil Bielowka

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Display_const.h>
#include <Display_const.h>
#include "stm32f4xx_hal.h"

typedef enum {vertical_1, horizontal_1, vertical_2, horizontal_2} display_orientation;

typedef struct
{
	uint16_t displayWidth;
	uint16_t displayHeight;
	display_orientation orientation;

} DisplayInfo;

/*	perform display hardware reset */
void DisplayHardwareReset();

/* Enables display using Reset pin (reset bit to "1")	*/
void DisplayHardwareEnable();

/*	Disables display using Reset pin (reset bit to "0")	*/
void DisplayHardwareDisable();

/*	Performs basic display init. After this function you can use drawing functions	*/
void DisplayInit();

/*	Sets display orientation	*/
void DisplaySetRotation(display_orientation newOrientation);

/*	fills screen with color	*/
void DisplayFillScreen(uint16_t color);

/*	Sets location of block to draw into. After using this function it is recommended	*/
/*	to use DisplayDrawColourBlock or DisplayDrawImageBlock to fill selected block.		*/
/*	Have in mind that image and color block should have size the same as choosen block	*/
void DisplaySetDrawBlock(uint16_t X1, uint16_t X2, uint16_t Y1, uint16_t Y2);

/*	Draws pixel	*/
void DisplayDrawPixel(uint16_t X, uint16_t Y, uint16_t color);

/*	Draws block with selected color	*/
void DisplayDrawColorBlock(uint16_t color, uint32_t size);

/*	Draws image into selected color	*/
void DisplayDrawImageBlock(uint8_t * buffer, uint16_t bufferSize);



#endif /* DISPLAY_H_ */
