#include "main.h"
void GPIO_Setup();
uint32_t temp;

void Delay_us(uint32_t time)
{
  while(time)
  {
  SysTick->LOAD = 168U-1U;
  SysTick->VAL = 0U;
  SysTick->CTRL = 5U;
  while(!(SysTick->CTRL & (1U << 16U)))
  {}
  --time;
  }
}

void main()
{
  GPIO_Setup();
  
  while(1)
  {
    GPIO_ToggleBits(GPIOA, GPIO_Pin_6);
    GPIO_ToggleBits(GPIOA, GPIO_Pin_7);
/*    temp = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_6);
    printf("%d \n", temp);
    printf("%d \n", SystemCoreClock);
*/
    Delay_us(100000);
  }
  
}
void GPIO_Setup()
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}