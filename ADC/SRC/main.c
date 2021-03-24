#include <main.h>
// ADC - PA1
void leds_init() {
GPIO_InitTypeDef gpio;
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
GPIO_StructInit(&gpio);
gpio.GPIO_Mode = GPIO_Mode_AN;  // Mode Analog
gpio.GPIO_Pin = GPIO_Pin_1;
GPIO_Init(GPIOA, &gpio);
}
void adc_init() {
ADC_InitTypeDef ADC_InitStructure;
ADC_CommonInitTypeDef adc_init;           // Cau truc chung
RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);    // Clock
/*  Function used to set the ADC configuration to the default reset state *****/  
ADC_DeInit();
/* Config ADC */
ADC_StructInit(&ADC_InitStructure);       // Global features of the ADC
adc_init.ADC_Mode = ADC_Mode_Independent;
adc_init.ADC_Prescaler = ADC_Prescaler_Div2;
ADC_CommonInit(&adc_init);              // Initializes the ADC peripheral

ADC_InitStructure.ADC_ScanConvMode = DISABLE;
ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
ADC_Init(ADC1, &ADC_InitStructure);     // Config Global features of  ADC
ADC_Cmd(ADC1, ENABLE);                  // Enable ADC Peripheral
}
u16 readADC1(u8 channel)
{
ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_3Cycles);// Config regular ADC (rank and sample time)
ADC_SoftwareStartConv(ADC1);            // Enable the selected ADC Software
while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
return ADC_GetConversionValue(ADC1);
}

int main(void)
{
leds_init();
adc_init();
while (1)
{
unsigned int bin_code = readADC1(ADC_Channel_1);
double voltage = bin_code * 3.3 / 0xfff;           // FFF = 2^12-1
printf("Voltage = %f\n",voltage);
Delay(50);
}
}