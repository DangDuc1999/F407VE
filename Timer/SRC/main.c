#include "main.h"
void INTTIM_Config(uint32_t time);
void GPIO_Config(void);
// TIM2_5-32bit
int main(void)
{
SystemInit();
GPIO_Config();
INTTIM_Config(1000); // = delay
while(1)
{ }
}
void TIM2_IRQHandler(void)  //  Ham xu ly ngat timer    // TIM
{
if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)      // TIM
{
TIM_ClearITPendingBit(TIM2, TIM_IT_Update);             // TIM
GPIO_ToggleBits(GPIOA,GPIO_Pin_6);
}
}
// Led
void GPIO_Config(void)
{
GPIO_InitTypeDef gpio_struct;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
gpio_struct.GPIO_Pin = GPIO_Pin_6;
gpio_struct.GPIO_Mode = GPIO_Mode_OUT;
gpio_struct.GPIO_OType = GPIO_OType_PP;
gpio_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
gpio_struct.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_Init(GPIOA, &gpio_struct);
}
void INTTIM_Config(uint32_t time)
{
  // Baat NIVC de su dung ngat
NVIC_InitTypeDef nvic_struct;
nvic_struct.NVIC_IRQChannel = TIM2_IRQn;                // TIM
nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
nvic_struct.NVIC_IRQChannelSubPriority = 1;
nvic_struct.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&nvic_struct);
// Cau hinh TIM2
TIM_TimeBaseInitTypeDef tim_struct;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  // TIM clock
tim_struct.TIM_Period = time*1000-1;   // Chu ki timer
tim_struct.TIM_Prescaler = (uint16_t)(SystemCoreClock/2/1000000)-1; // Bo chia tan so -63
tim_struct.TIM_ClockDivision = 0;
tim_struct.TIM_CounterMode = TIM_CounterMode_Up;  // Dem len
TIM_TimeBaseInit(TIM2, &tim_struct);                    // TIM
// Ngat timer
TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  // Su dung ngat timer  // TIM
TIM_Cmd(TIM2, ENABLE);   // Bat TIM counter             // TIM
}
