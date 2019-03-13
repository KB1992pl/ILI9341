/*
 * spi.c
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

#include "spi.h"
#include "pins_def.h"

extern SPI_HandleTypeDef hspi1;


void SpiSendDataByte(uint8_t data)
{
	DC_PIN_SET;
	CS_PIN_RESET;
	HAL_SPI_Transmit(&hspi1, &data, 1, SPI_TIMEOUT);
	CS_PIN_SET;
}

void SpiSendCommandByte(uint8_t command)
{
	DC_PIN_RESET;
	CS_PIN_RESET;
	HAL_SPI_Transmit(&hspi1, &command, 1, SPI_TIMEOUT);
	CS_PIN_SET;
}

void SpiSendDataBuffer(uint8_t * data, uint16_t size)
{
	DC_PIN_SET;
	CS_PIN_RESET;
	HAL_SPI_Transmit(&hspi1, data, size, SPI_TIMEOUT);
	CS_PIN_SET;
}

void SpiTransmit(uint8_t * data, uint32_t size)
{
	HAL_SPI_Transmit(&hspi1, data, size, SPI_TIMEOUT);
}

void SpiTransmitBlock(uint8_t command, uint8_t *dataBuffer, uint32_t dataBufferSize)
{
	DC_PIN_RESET;
	CS_PIN_RESET;
	HAL_SPI_Transmit(&hspi1, &command, 1, SPI_TIMEOUT);
	DC_PIN_SET;
	HAL_SPI_Transmit(&hspi1, dataBuffer, dataBufferSize, SPI_TIMEOUT);
	CS_PIN_SET;
}

