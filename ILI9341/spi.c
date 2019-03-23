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
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal.h"
#include "main.h"

SPI_HandleTypeDef hspi1;

#ifdef FAST_SPI
volatile uint8_t * DR_register;
#define WAIT_SPI_READY		while(!(__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_TXE))){}
#endif

void Spi1Init()
{
	__HAL_RCC_SPI1_CLK_ENABLE();
	hspi1.Instance = SPI1;
	 hspi1.Init.Mode = SPI_MODE_MASTER;
	 hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	 hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	 hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	 hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	 hspi1.Init.NSS = SPI_NSS_SOFT;
	 hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	 hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	 hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	 hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	 hspi1.Init.CRCPolynomial = 15;
	 if (HAL_SPI_Init(&hspi1) != HAL_OK)
	  {
	    Error_Handler();
	  }

#ifdef FAST_SPI
	 uint8_t data=0;
	 DR_register = &(hspi1.Instance->DR);
	 HAL_SPI_Transmit(&hspi1, &data, 1, SPI_TIMEOUT);	//used to enable SPI
#endif
}

void SpiSendDataByte(uint8_t data)
{
	DC_PIN_SET;
	CS_PIN_RESET;

#ifdef FAST_SPI
	WAIT_SPI_READY;
	*DR_register = data;
#else
	HAL_SPI_Transmit(&hspi1, &data, 1, SPI_TIMEOUT);
#endif

	CS_PIN_SET;
}



void SpiSendCommandByte(uint8_t command)
{
	DC_PIN_RESET;
	CS_PIN_RESET;

#ifdef FAST_SPI
	WAIT_SPI_READY;
	*DR_register = command;
#else
	HAL_SPI_Transmit(&hspi1, &command, 1, SPI_TIMEOUT);
#endif

	CS_PIN_SET;
}

void SpiSendDataBuffer(uint8_t * data, uint32_t bufferSize)
{
	DC_PIN_SET;
	CS_PIN_RESET;

#ifdef FAST_SPI
	for (uint32_t i = 0; i< bufferSize; i++)
	{
		WAIT_SPI_READY;
		*DR_register = data[i];
	}
#else
	HAL_SPI_Transmit(&hspi1, data, bufferSize, SPI_TIMEOUT);
#endif

	CS_PIN_SET;
}

void SpiSendDataRepeated(uint8_t * data, uint32_t bufferSize, uint32_t repeats)
{
	DC_PIN_SET;
	CS_PIN_RESET;
	for (uint32_t i =0; i < repeats;i++)
	{

#ifdef FAST_SPI
		for (uint32_t j = 0; j < bufferSize; j++)
		{
			WAIT_SPI_READY;
		    *DR_register = data[j];
		}

#else
		HAL_SPI_Transmit(&hspi1, data, bufferSize, SPI_TIMEOUT);
#endif

	}
	CS_PIN_SET;
}

void SpiTransmit(uint8_t * data, uint32_t size)
{
#ifdef FAST_SPI
	for (uint32_t i=0;i<size;i++)
	{
		WAIT_SPI_READY;
		*DR_register = data[i];
	}
#else
	HAL_SPI_Transmit(&hspi1, data, size, SPI_TIMEOUT);
#endif
}

void SpiTransmitBlock(uint8_t command, uint8_t *dataBuffer, uint32_t dataBufferSize)
{
	DC_PIN_RESET;
	CS_PIN_RESET;

#ifdef FAST_SPI
	WAIT_SPI_READY;
	*DR_register = command;
#else
	HAL_SPI_Transmit(&hspi1, &command, 1, SPI_TIMEOUT);
#endif

	DC_PIN_SET;

#ifdef FAST_SPI
	for (uint32_t i = 0 ; i<dataBufferSize;i++)
	{
		WAIT_SPI_READY;
		*DR_register = dataBuffer[0];
	}
#else
	HAL_SPI_Transmit(&hspi1, dataBuffer, dataBufferSize, SPI_TIMEOUT);
#endif

	CS_PIN_SET;
}

