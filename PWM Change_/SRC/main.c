#include "main.h"

void GPIOinit();
void TimerInit();
int main(void)
{
SystemInit();
GPIOinit();
TimerInit();
int brightness = 0;
int i;
while(1)
{
brightness++;
TIM3->CCR3 = 333 - (brightness + 0) % 333;
TIM3->CCR4 = 333 - (brightness + 166 / 2) % 333;
TIM3->CCR1 = 333 - (brightness + 333 / 2) % 333;
TIM3->CCR2 = 333 - (brightness + 499 / 2) % 333;
for(i=0;i < 50000; ++i);
}
}
void GPIOinit()
{
GPIO_InitTypeDef gpio_init;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
gpio_init.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
gpio_init.GPIO_Mode = GPIO_Mode_AF;
gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
gpio_init.GPIO_OType = GPIO_OType_PP;
gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOA, &gpio_init);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM3);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM3);
}
void TimerInit()
{
TIM_TimeBaseInitTypeDef time_init;
TIM_OCInitTypeDef oc_init;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
uint16_t PrescalerValue = (uint16_t)((SystemCoreClock / 2) / 21000000);
time_init.TIM_Period = 665;
time_init.TIM_Prescaler = PrescalerValue;
time_init.TIM_ClockDivision = 0;
time_init.TIM_CounterMode = TIM_CounterMode_Up;
TIM_TimeBaseInit(TIM3, &time_init);
//
oc_init.TIM_OCMode = TIM_OCMode_PWM1;
oc_init.TIM_OutputState = TIM_OutputState_Enable;
oc_init.TIM_Pulse = 0;
oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
TIM_OC1Init(TIM3, &oc_init);
TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
//
oc_init.TIM_OutputState = TIM_OutputState_Enable;
oc_init.TIM_Pulse = 0;
TIM_OC2Init(TIM3, &oc_init);
TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
//
printf("PrescalerValue = %d",PrescalerValue);
}