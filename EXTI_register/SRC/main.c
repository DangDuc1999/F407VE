#include "main.h"
void GPIO_Config();
void EXTILine4_Config();
void EXTI4_IRQHandler(void);
uint32_t temp;
uint32_t count = -1;
void main()
{
  GPIO_Config();
  EXTILine4_Config();
  while(1)
  {}
  
}
void GPIO_Config()
{
  RCC->AHB1ENR    = 0x01;       // Enable GPIOA
  GPIOA->MODER   &= 0xFFFF0FFF; // Reset Port PA6, PA7
  GPIOA->MODER   |= 0x5000;     // Set mode OUT PA6, PA7
  GPIOA->OTYPER  |= 0x00;       // Push-pull
  GPIOA->OSPEEDR |= 0xF0000;    // Speed very high
  GPIOA->PUPDR   |= 0x00;       // No pull-up pull-down	
  GPIOA->BSRRL   |= 0x03 << 6;  // Set pin 6 + 7
}

void EXTILine4_Config()
{
  // Enable clock
  RCC->AHB1ENR |= 0x01 << 4; // Enable GPIOE
  RCC->APB2ENR = 0x01  << 14; // Enable SYSCFG Clock
  // Button
  GPIOE->MODER &= 0x00 << 8; // INPUT port PE4
  GPIOE->PUPDR |= 0x01 << 8; // Pull UP
  // Connect EXTI Line4 to PA4 Pin
  SYSCFG->EXTICR[1] &= 0x00;  // Reset
  SYSCFG->EXTICR[1] |= 0x04;  // Select PE: 0100 Register 2
  // Config EXTI Line4
  EXTI->IMR   |= 0x01 << 4; // Enable Interrupt Mask
  EXTI->FTSR  |= 0x01 << 4; // Falling Trigger Selected
  EXTI->PR    |= 0x00 << 4; // Set Pending Bit = 1
  EXTI->SWIER |= 0x01 << 4; // Sofware Interrupt
  
  /* EXTI Line 4 */
  NVIC->STIR = 10;            // IRQ4
  NVIC->IP[10] |= 0x01;       // Priority 0 IP[priority in vector table] = priority
  NVIC->ISER[0] = 0xFFFFFFFF; // Enable

}

void EXTI4_IRQHandler(void) // Ham xu ly ngat  U-STD 
{ 
  count++;
  if(EXTI_GetITStatus(EXTI_Line4) != RESET)
  {
    if(count == 0)
    {
      GPIOA->BSRRL |= 0x03 << 6; // Set pin 6 + 7
    }
    if(count == 1)
    {
      GPIOA->BSRRH |= 0x01 << 6; // Reset pin 6
      GPIOA->BSRRL |= 0x01 << 7; // Set pin 7
    }
    if(count == 2)
    {
      GPIOA->BSRRH |= 0x01 << 7; // Reset pin 7
      GPIOA->BSRRL |= 0x01 << 6; // Set pin 6
    }
    if(count == 3)
    {
      GPIOA->BSRRH |= 0x03 << 6; // Reset pin 6 + 7
    }
    if(count == 4)
    {
      count = 0;
      GPIOA->BSRRL |= 0x03 << 6; // Set pin 6 + 7
    }
    /* Clear the EXTI line 4 pending bit */
      EXTI->PR     |= 0x01 << 4;
  }
}