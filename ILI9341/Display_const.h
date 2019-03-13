/*
 * Display_commands.h
 *
 *  Created on: 10.03.2019
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

#ifndef DISPLAY_CONST_H_
#define DISPLAY_CONST_H_

#define DISPLAY_WIDTH 						240
#define DISPLAY_HEIGHT						320

/*	commands	*/
#define DISPLAY_COMMAND_NOP 				0x00
#define DISPLAY_COMMAND_SOFT_RESET			0x01
#define DISPLAY_COMMAND_SLEEP_ON			0x10	//enter sleep mode
#define DISPLAY_COMMAND_SLEEP_OFF			0x11	//sleep out
#define DISPLAY_COMMAND_PARTIAL_MODE_ON		0x12
#define DISPLAY_COMMAND_NORMAL_MODE_ON		0x13	//normal display mode on
#define DISPLAY_COMMAND_INVERSION_OFF		0x20	//display inversion off
#define DISPLAY_COMMAND_INVERSION_ON		0x21	//display inversion on
#define DISPLAY_COMMAND_GAMMA_SET			0x26
#define DISPLAY_COMMAND_DISPLAY_OFF			0x28
#define DISPLAY_COMMAND_DISPLAY_ON			0x29
#define DISPLAY_COMMAND_COL_ADDR_SET		0x2A	//column address set
#define DISPLAY_COMMAND_PAGE_ADDR_SET		0x2B	//page address set
#define DISPLAY_COMMAND_MEMORY_WRITE		0x2C
#define DISPLAY_COMMAND_COLOR_SET			0x2D
#define DISPLAY_COMMAND_PARTIAL_AREA		0x30
#define DISPLAY_COMMAND_VERTICAL_SCROLL		0x33	//vertical scrolling definition
#define DISPLAY_COMMAND_TEARING_OFF			0x34	//tearing effect line OFF
#define DISPLAY_COMMAND_TEARING_ON			0x35	//tearing effect line ON
#define DISPLAY_COMMAND_MEM_ACCESS_CTRL		0x36	//memory access control - used for orientation change
#define DISPLAY_COMMAND_IDLE_MODE_OFF		0x38
#define DISPLAY_COMMAND_IDLE_MODE_ON		0x39
#define DISPLAY_COMMAND_PIXEL_FORMAT_SET	0x3A
#define DISPLAY_COMMAND_SET_TEAR_SCANLINE	0x44
#define DISPLAY_COMMAND_WRITE_DISP_BRIGHT	0x51	//write display brightness
#define DISPLAY_COMMAND_WRITE_CTRL_DISPLAY	0x53
#define DISPLAY_COMMAND_RGB_INTERFACE		0xB0
#define DISPLAY_COMMAND_FRAME_CONTROL_NORM	0xB1	//valid in normal mode
#define DISPLAY_COMMAND_FRAME_CONTROL_IDLE	0xB2	//valid in idle mode
#define DISPLAY_COMMAND_FRAME_CONTROL_PART	0xB3	//valid in partial mode
#define DISPLAY_COMMAND_DISPLAY_INV_CTRL	0xB4	//display inversion control
#define DISPLAY_COMMAND_BLANKING_PORCH_CTRL	0xB5	//blanking proch control
#define DISPLAY_COMMAND_FUNC_CTRL			0xB6	//display function control
#define DISPLAY_COMMAND_POWER_CONTROL_1		0xC0
#define DISPLAY_COMMAND_POWER_CONTROL_2		0xC1
#define DISPLAY_COMMAND_POS_GAMMA_CTRL		0xE0	//positive gamma correction
#define DISPLAY_COMMAND_NEG_GAMMA_CTRL		0xE1	//negative gamma correction

#define RESET_DELAY							300
#define SLEEP_DELAY							150

/*	registers	*/

//memory access control registers
/* These 3 bits control MCU to memory write/read direction. */
#define MEM_ACCESS_DEFAULT					0x00
#define MEM_ACCESS_CTRL_MY					(1<<7)
#define MEM_ACCESS_CTRL_MX					(1<<6)
#define MEM_ACCESS_CTRL_MV					(1<<5)	//Row/column exchange

#define MEM_ACCESS_CTRL_ML					(1<<4)	//LCD vertical refresh direction control. "0" - top to bottom, "1" bottom to top
#define MEM_ACCESS_CTRL_BGR					(1<<3)	//Color selector switch control (0=RGB color filter panel, 1=BGR color filter panel)
#define MEM_ACCESS_CTRL_MH					(1<<2)	//LCD horizontal refreshing direction control. "0" - left to right, "1" - right to left

//pixel format set registers
#define PIXEL_FORMAT_RGB_16BITS				(0b101<<3)
#define PIXEL_FORMAT_RGB_18BITS				(0b110<<3)
#define PIXEL_FORMAT_MCU_16BITS				(0b101)
#define PIXEL_FORMAT_MCU_18BITS				(0b110)

#define BURST_MAX_SIZE 					500
#define COLOR_BUFFER_SIZE 				2
#define COORDINATES_BUFFER_SIZE			4

/*	colors */
#define COLOR_BLACK       0x0000
#define COLOR_NAVY        0x000F
#define COLOR_DARKGREEN   0x03E0
#define COLOR_DARKCYAN    0x03EF
#define COLOR_MAROON      0x7800
#define COLOR_PURPLE      0x780F
#define COLOR_OLIVE       0x7BE0
#define COLOR_LIGHTGREY   0xC618
#define COLOR_DARKGREY    0x7BEF
#define COLOR_BLUE        0x001F
#define COLOR_GREEN       0x07E0
#define COLOR_CYAN        0x07FF
#define COLOR_RED         0xF800
#define COLOR_MAGENTA     0xF81F
#define COLOR_YELLOW      0xFFE0
#define COLOR_WHITE       0xFFFF
#define COLOR_ORANGE      0xFD20
#define COLOR_GREENYELLOW 0xAFE5
#define COLOR_PINK        0xF81F
#endif /* DISPLAY_CONST_H_ */
