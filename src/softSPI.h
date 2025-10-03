
#ifndef _SOFTSPI_H_
#define _SOFTSPI_H_

#include "REGX52.H"

#define SPI_SCLK P0_7

#define SPI_MOSI P0_6

// 液晶控制口置1操作语句宏定义

#define SPI_MOSI_SET P0_6 = 1
#define SPI_SCLK_SET P0_7 = 1
// 液晶控制口置0操作语句宏定义

#define SPI_MOSI_CLR P0_6 = 0
#define SPI_SCLK_CLR P0_7 = 0

void SPIv_WriteData(unsigned char Data);

#endif
