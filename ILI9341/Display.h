/*
 * Display.h
 *
 *  Created on: 09.03.2019
 *      Author: KB1992pl
 *      https://github.com/KB1992pl/
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
void DisplayDrawColorBlock(uint16_t color, uint16_t size);

/*	Draws image into selected color	*/
void DisplayDrawImageBlock(uint8_t * buffer, uint16_t bufferSize);



#endif /* DISPLAY_H_ */
