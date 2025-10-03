#include "softSPI.h"

void SPIv_WriteData(unsigned char Data)
{
  unsigned char i = 0;
  for (i = 8; i > 0; i--)
  {
    if (Data & 0x80)
      SPI_MOSI_SET; // 输出数据
    else
      SPI_MOSI_CLR;

    SPI_SCLK_CLR;
    SPI_SCLK_SET;
    Data <<= 1;
  }
}
