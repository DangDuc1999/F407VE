#include "main.h"
void GPIO_Config();
uint32_t temp;
void main()
{
  GPIO_Config();
  
  while(1)
  {
    GPIOA->ODR ^= 0x03 << 6; //0xC0
    Delay(1000);
 // temp = GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_6);
 // printf("%d \n", temp);
  }
  
}
void GPIO_Config()
{
  RCC->AHB1ENR = 0x01; // Enable GPIOA
  GPIOA->MODER &= 0xFFFF0FFF;// Reset Port PA6, PA7
  GPIOA->MODER |= 0x05 << 12; // Set mode PA6, PA7 0x5000
  GPIOA->OTYPER |= 0x00; // Push-pull
  GPIOA->OSPEEDR |= 0xF000; // Speed very high
  GPIOA->PUPDR |= 0xFFFFFFFF; // No pull-up pull-down	
}