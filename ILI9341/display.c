/*
 * display.c
 *
 *  Created on: 09.03.2019
 *      Author: KB1992pl
 *      https://github.com/KB1992pl/
 */

#include <Display.h>
#include <Display_const.h>
#include "pins_def.h"

DisplayInfo info;

void DisplayHardwareReset()
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET);
	HAL_Delay(RESET_DELAY);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET);
	HAL_Delay(RESET_DELAY);
}

void DisplayHardwareEnable()
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET);
}

void DisplayHardwareDisable()
{
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET);
}

void DisplayInit()
{
	DisplayHardwareReset();

	SpiSendCommandByte(DISPLAY_COMMAND_PIXEL_FORMAT_SET);
	SpiSendDataByte(PIXEL_FORMAT_MCU_16BITS|PIXEL_FORMAT_RGB_16BITS);

	SpiSendCommandByte(DISPLAY_COMMAND_SLEEP_OFF);
	HAL_Delay(SLEEP_DELAY);

	DisplaySetRotation(vertical_1);

	SpiSendCommandByte(DISPLAY_COMMAND_DISPLAY_ON);
}

void DisplaySetRotation(display_orientation newOrientation)
{
	SpiSendCommandByte(DISPLAY_COMMAND_MEM_ACCESS_CTRL);
	switch (newOrientation)
	{
	case vertical_1:
		SpiSendDataByte(MEM_ACCESS_DEFAULT);
		info.displayWidth =DISPLAY_WIDTH;
		info.displayHeight = DISPLAY_HEIGHT;
		info.orientation = vertical_1;
		break;
	case horizontal_1:
		SpiSendDataByte((MEM_ACCESS_CTRL_MV)|(MEM_ACCESS_CTRL_MX));
		info.displayWidth =DISPLAY_HEIGHT;
		info.displayHeight = DISPLAY_WIDTH;
		info.orientation = horizontal_1;
		break;
	case vertical_2:
		SpiSendDataByte((MEM_ACCESS_CTRL_MY)|(MEM_ACCESS_CTRL_MX));
		info.displayWidth =DISPLAY_WIDTH;
		info.displayHeight = DISPLAY_HEIGHT;
		info.orientation = vertical_2;
		break;
	case horizontal_2:
		SpiSendDataByte((MEM_ACCESS_CTRL_MY)|(MEM_ACCESS_CTRL_MV));
		info.displayWidth =DISPLAY_HEIGHT;
		info.displayHeight = DISPLAY_WIDTH;
		info.orientation = horizontal_2;
		break;
	}
}
void DisplayFillScreen(uint16_t color)
{
	DisplaySetDrawBlock(0, info.displayWidth, 0, info.displayHeight);
	DisplayDrawColorBlock(color,(info.displayWidth * info.displayHeight));
}

void DisplaySetDrawBlock(uint16_t X1, uint16_t X2, uint16_t Y1, uint16_t Y2)
{
	SpiSendCommandByte(DISPLAY_COMMAND_COL_ADDR_SET);
	SpiSendDataByte(X1>>8);
	SpiSendDataByte(X1);
	SpiSendDataByte(X2>>8);
	SpiSendDataByte(X2);

	SpiSendCommandByte(DISPLAY_COMMAND_PAGE_ADDR_SET);
	SpiSendDataByte(Y1>>8);
	SpiSendDataByte(Y1);
	SpiSendDataByte(Y2>>8);
	SpiSendDataByte(Y2);

	SpiSendCommandByte(DISPLAY_COMMAND_MEMORY_WRITE);

}
void DisplayDrawPixel(uint16_t X, uint16_t Y, uint16_t color)
{
	//X data
	{
	SpiSendCommandByte(DISPLAY_COMMAND_COL_ADDR_SET);
	uint8_t tempBuffer[COORDINATES_BUFFER_SIZE] = {X>>8, X, (X+1)>>8, (X+1)};
	SpiSendDataBuffer(tempBuffer, COORDINATES_BUFFER_SIZE);
	}
	//Y data
	{
		SpiSendCommandByte(DISPLAY_COMMAND_PAGE_ADDR_SET);
		uint8_t tempBuffer[COORDINATES_BUFFER_SIZE] = {Y>>8, Y, (Y+1)>>8, (Y+1)};
		SpiSendDataBuffer(tempBuffer, COORDINATES_BUFFER_SIZE);
	}
	//Color data
	{
		SpiSendCommandByte(DISPLAY_COMMAND_MEMORY_WRITE);
		uint8_t colorBuffer[COLOR_BUFFER_SIZE] = {color>>8, color};
		SpiSendDataBuffer(colorBuffer, COLOR_BUFFER_SIZE);
	}
}

void DisplayDrawColorBlock(uint16_t color, uint16_t size)
{
	uint8_t colorBuffer[COLOR_BUFFER_SIZE] = {color>>8, color};
	for (uint16_t i = 0; i< size*2;i++)
	{
		SpiSendDataBuffer(colorBuffer,COLOR_BUFFER_SIZE);
	}
}

void DisplayDrawImageBlock(uint8_t * buffer, uint16_t bufferSize)
{
	SpiSendDataBuffer(buffer, bufferSize);
}
