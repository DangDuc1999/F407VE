#include "Delay.h"

void Delay_us(uint32_t time)
{
  while(time)
  {
  SysTick->LOAD = 168-1;
  SysTick->VAL = 0;
  SysTick->CTRL = 5U;
  while(!(SysTick->CTRL & (1U<<16U)))
  {}
  --time;
  }
}
void Delay(uint32_t time)
{
  while(time)
  {
    SysTick->LOAD = 168*1000 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = 5U;
    while(!(SysTick->CTRL & (1U<<16U)))
    {}
    --time;
  }
}