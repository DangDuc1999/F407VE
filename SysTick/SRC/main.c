// SYSTICK -> Main.c
#include "main.h"

void EXTILine4_Config();
__IO uint32_t count = -1;
void GPIO_Config();
void main(void)
{
  SystemInit();
  GPIO_Config();
  while(1)
  {
  GPIO_ToggleBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_7);
  Delay(100);
  }
}


void GPIO_Config()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA,GPIO_Pin_6 | GPIO_Pin_7);
}
