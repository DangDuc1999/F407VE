#include "main.h"
void GPIO_Setup();
void ADC_Config();
uint32_t temp;
#define ARRAYSIZE 800
#define ADC1_DR_ADDRESS (uint32_t) 0x4001204C
volatile uint32_t status = 0;
__IO uint32_t ADCComvertedValue = 0;
 uint32_t Voltage = 0;
 uint32_t Analog = 0;
void main()
{
  SystemInit();
  GPIO_Setup();

  ADC_Config();
  // Start ADC Software Conversion
  ADC_SoftwareStartConv(ADC1);
  
  while(1)
  {
    GPIO_ToggleBits(GPIOA, GPIO_Pin_6|GPIO_Pin_7);
    Voltage = ADCComvertedValue*3300/0xFFF;
    printf("Voltage = %d \n", Voltage);
    Analog = ADC_GetConversionValue(ADC1);
    printf("Analog = %d\n",Analog);
    Delay(500);
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
void ADC_Config()
{
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef DMA_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  // ADC, DMA, GPIO clock
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  
  // DMA2 stream channel x configuration
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;// Luong x - hoat dong nhu 1 luong doc lap
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) &ADCComvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;  // Chuyen du ieu tu ngoai vi den bo nho
  DMA_InitStructure.DMA_BufferSize = 1; // Kich thuoc du lieu
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // Nen tat
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;       // Nen bat
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // Kich thuoc ngoai vi
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // Kich thuoc bo nho
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; // Vong tron tu nap lai
  DMA_InitStructure.DMA_Priority = DMA_Priority_High; // Uu tien
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;   // First in first out
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull; // Nguong cua FIFO
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; // Gioi han truyen cua bo nho
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;// Gioi han truyen cua ngoai vi
  DMA_Init(DMA2_Stream0,&DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);
  // Config ADC3 channel2 stream0 as analog input      manual page 308
  ADC_DeInit(); // Set peripheral to default
  GPIO_StructInit(&GPIO_InitStructure);// Reset ve gia tri mac dinh
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN; // Mode analog
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  
  // ADC Common Init
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//?
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);
  
  // ADC3 Init
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;// Doc ngoai vi theo canh
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;// ?
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;// So luong chuyen doi ADC duoc su dung cho nhom channel
  ADC_Init(ADC1, &ADC_InitStructure);
  
  // ADC3 channel2 config
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0,1, ADC_SampleTime_3Cycles);
  // Enable DMA request after last transfer (Single-ADC mode)
  ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
  // Enable ADC3 DMA
  ADC_DMACmd(ADC1,ENABLE);
  //Enable ADC3
  ADC_Cmd(ADC1,ENABLE);
}