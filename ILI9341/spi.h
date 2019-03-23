/*
 * spi.h
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

#ifndef SPI_H_
#define SPI_H_
#include "stm32f4xx_hal.h"

#define SPI_TIMEOUT 10

/*	Define FAST_SPI allows to override sending functions, but
 * 	they return no error codes. FAST_SPI only sends data and waits
 * 	until SPI is ready to send new data. Comment this define to
 * 	use standard HAL_SPI functions.
 */
#define FAST_SPI

#define DC_PIN_SET		HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_SET)
#define DC_PIN_RESET	HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,GPIO_PIN_RESET)
#define CS_PIN_SET		HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_SET)
#define CS_PIN_RESET	HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,GPIO_PIN_RESET)

/*	Inits SPI1 instance	*/
void Spi1Init();

/*	Sends byte of data. Function also sets CS and DC bits	*/
void SpiSendDataByte(uint8_t data);

/*	Sends byte of command. Function also sets CS and DC bits	*/
void SpiSendCommandByte(uint8_t command);

/*	Sends "size" bytes of data. Function also sets CS and DC bits	*/
void SpiSendDataBuffer(uint8_t * data, uint32_t bufferSize);

/*	works similar to SpiSendDataBuffer, but repeats sending buffer before
 * 	setting CS bit. Recommended for drawing big surfaces with one color
 */
void SpiSendDataRepeated(uint8_t * data, uint32_t bufferSize, uint32_t repeats);

/*	Sends "size" bytes via SPI. Funcion DOESN'T set CS and DC bits	*/
void SpiTransmit(uint8_t * data, uint32_t bufferSize);

/*	Sends command and "dataBufferSize" of data. Function also sets CS and DC bits	*/
void SpiTransmitBlock(uint8_t command, uint8_t *dataBuffer, uint32_t dataBufferSize);

#endif /* SPI_H_ */
