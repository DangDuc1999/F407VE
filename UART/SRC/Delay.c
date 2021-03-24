#include "Delay.h"

static uint32_t TimingDelay;
void Delay(uint32_t nTime)
{
  // Call systick
  if (SysTick_Config(SystemCoreClock / 1000))
    {
    /* Capture error */
  while (1);
    }
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void SysTick_Handler(void)
{
    if (TimingDelay != 0x00)
    {
    TimingDelay--;
    }
}