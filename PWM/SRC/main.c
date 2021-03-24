#include "main.h"
void InitializeGPIO(GPIO_TypeDef* GPIOx, uint32_t Pin);
void InitializeTimer(TIM_TypeDef* TIMx, uint16_t PrescaleDiv, uint16_t Period);
void InitializePWMChannel4(TIM_TypeDef* TIMx, uint32_t ValueToOn);
void main( )
{
// Khoi tao tan so he thong
SystemInit();
// Khoi tao cong GPIO
RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
InitializeGPIO( GPIOA, GPIO_Pin_6);                 // USER
// Khoi tao Timer 4
// prescaler*period = 60000*2800 (voi SysClk = 168 MHz tan so PWM se la 1 Hz)
RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM4, ENABLE );
InitializeTimer( TIM4, 60000 - 1, 2800-1 );           // USER
// Khoi tao PWM Chanel4
// 50% duty factor = 1400
InitializePWMChannel4( TIM4, 27999 );                 // USER
GPIO_PinAFConfig( GPIOA, GPIO_PinSource6, GPIO_AF_TIM4 );  // STD
}
/**
* @brief Setup the GPIOx port as out of PWM on selected Pin.
* @param GPIOx: where x can be (A..I) to select the GPIO peripheral.
* @param Pin: specifies the port bit to be initialized for out of PWM signal.
* Refer STM32F407xx Datasheet for Alternate function mapping (Table 9)
* @retval None
*/
void InitializeGPIO(GPIO_TypeDef* GPIOx, uint32_t Pin)
{
GPIO_InitTypeDef sg;
sg.GPIO_Pin = Pin;
sg.GPIO_Mode = GPIO_Mode_AF; // PWM is Alternate function Mode
sg.GPIO_Speed = GPIO_Speed_100MHz;
sg.GPIO_OType = GPIO_OType_PP;
sg.GPIO_PuPd = GPIO_PuPd_DOWN;
GPIO_Init( GPIOx, &sg );
}
/**
* @brief Initialize timer TIMx as counter with the specified Period and Prescaler.
* @param TIMx: where x can be 1 to 14 to select the TIM peripheral.
* @param Period: the length of period will be n+1 because the counting begin from 0
* @param PrescaleDiv: Divides the clock at PrescaleDiv+1.
* If PrescaleDiv=0 then SrcClock not changed.
* @retval None
*/
void InitializeTimer(TIM_TypeDef* TIMx, uint16_t PrescaleDiv, uint16_t Period) // USER
{
TIM_TimeBaseInitTypeDef sT;
sT.TIM_Prescaler = PrescaleDiv;
sT.TIM_CounterMode = TIM_CounterMode_Up;// Count to up
sT.TIM_Period = Period;
sT.TIM_ClockDivision = TIM_CKD_DIV1; // No pre-division
sT.TIM_RepetitionCounter = 0;
TIM_TimeBaseInit( TIMx, &sT );
TIM_Cmd( TIMx, ENABLE );    // Bat counter
}
/**
* @brief Initialize PWM channel 4 of TIMx
* @param TIMx: where x can be 1 to 14 to select the TIM peripheral.
* @param ValueToOn: the value of TIMx starting from which PWM out will be 1
* @retval None
*/
void InitializePWMChannel4 ( TIM_TypeDef* TIMx, uint32_t ValueToOn )
{
TIM_OCInitTypeDef sOC;
sOC.TIM_OCMode = TIM_OCMode_PWM1;
sOC.TIM_Pulse = ValueToOn;
sOC.TIM_OutputState = TIM_OutputState_Enable;
sOC.TIM_OCPolarity = TIM_OCPolarity_High;
TIM_OC4Init( TIMx, &sOC);
TIM_OC4PreloadConfig( TIMx, TIM_OCPreload_Enable);
}