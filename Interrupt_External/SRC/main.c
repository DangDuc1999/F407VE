#include "main.h"
// Interrupt External
// gan cong tac vao chan PE4
void EXTILine4_Config(void);                            //           n
void LEDInit(void);
uint32_t count = -1;

void main(void)
{
/*!< At this stage the microcontroller clock setting is already configured,
this is done through SystemInit() function which is called from startup
file (startup_stm32f4xx.s) before to branch to application main.
To reconfigure the default setting of SystemInit() function, refer to
system_stm32f4xx.c file
*/
  SystemInit();
  LEDInit();
/* Initialize LED4 mounted on STM32F4-Discovery board */
/* Configure EXTI Line0 (connected to PA0 pin) in interrupt mode */
  EXTILine4_Config(); // U-STD                                  n
/* Generate software interrupt: simulate a rising edge applied on EXTI0 line */
  EXTI_GenerateSWInterrupt(EXTI_Line4);   // STD
while (1)
{ }
}
//  Led PA 6
void LEDInit()
{
  GPIO_InitTypeDef GPIO_InitStructure;
/* Enable the GPIO_LED Clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
/* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_7);
}
// Interrupt
void EXTILine4_Config(void)
{
//  GPIO_InitTypeDef GPIO_InitStructure;  //Cau hinh nut bam PE4
  EXTI_InitTypeDef EXTI_InitStructure;  // Xu ly tin hieu ngat
  NVIC_InitTypeDef NVIC_InitStructure;  // Bo xu ly ngat
  // Enable clock
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
  // Button
  RCC->AHB1ENR |= 0x01 << 4; // Enable GPIOE
  GPIOE->MODER &= 0x00 << 8; // INPUT port PE4
  GPIOE->PUPDR |= 0x01 << 8; // Pull UP
/*  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE,&GPIO_InitStructure); */
  // Connect EXTI Line4 to PA4 Pin
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
  // Config EXTI Line4
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  // Enable and Set EXTI Line4 Interrupt to the lowest priority
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void EXTI4_IRQHandler(void) // Ham xu ly ngat  U-STD                  - n
{ 
  count++;
  if(EXTI_GetITStatus(EXTI_Line4) != RESET)
  {
    if(count == 0)
  {
    GPIO_SetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_7);
  }
  if(count == 1)
  {
  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
  GPIO_SetBits(GPIOA,GPIO_Pin_7);
  }
  if(count == 2)
  {
  GPIO_ResetBits(GPIOA,GPIO_Pin_7);
  GPIO_SetBits(GPIOA,GPIO_Pin_6);
  }
  if(count == 3)
  {
  GPIO_ResetBits(GPIOA,GPIO_Pin_7);
  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
  }
  if(count == 4)
  {
  count = 0;
  GPIO_SetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_7);
  }
    
/* Clear the EXTI line 0 pending bit */
  EXTI_ClearITPendingBit(EXTI_Line4);  // STD                            - n
}
}