#include "main.h"

void GPIO_Config(void);
void USART_Config(void);
void USART6_Puts(char * str);
void NVIC_Config(void);
void main()
{
SystemInit(); // Initialize the Embedded Flash Interface, the PLL and update the System Frequency
GPIO_Config();
USART_Config();
NVIC_Config();
// Gui di chuoi "Hello World"
USART6_Puts("Hello World!\n");
while (1)
{
// Bat den LED o chan 6 cong A de bao hieu truyen du lieu
GPIO_ToggleBits(GPIOA, GPIO_Pin_6);
Delay(1000);
}
}
/*************************************************
Function: void GPIO_Config(void)
Description: Configure GPIOD to use LEDs
Input:
Output:
Return:
*************************************************/
void GPIO_Config(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
/* Ket noi GPIOD voi clock va bat clock */
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
/* Khoi tao cong D la output, chuan bi xuat du lieu ra chan 12 */
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
/* Goi ham khoi tao cong */
GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/*************************************************
Function: void USART_Config(void)
Description: Configure USART6 for serial communication
Input:
Output:
Return:
*************************************************/
void USART_Config(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
// Lien ket PC6 va PC7 voi TX va RX cua USART6
GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
// Cau hinh PC6 la chan TX, PC7 la chan RX cua USART6
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7;
// Thiet lap che do lam viec cua cong la Alternate Function (AF)
GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOC,&GPIO_InitStructure);
/*Thiet lap cac tham so truyen thong cho USART6*/
// Thiet lap hinh mac dinh
USART_StructInit(&USART_InitStructure);
// BaudRate = 115,2 kbits/s
USART_InitStructure.USART_BaudRate =115200;
// Data bits = 8
USART_InitStructure.USART_WordLength = USART_WordLength_8b;
// Stop bits = 1
USART_InitStructure.USART_StopBits = USART_StopBits_1;
// Parity = none
USART_InitStructure.USART_Parity = USART_Parity_No;
// Handshaking = none
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
// Cho phep truyen va nhan du lieu
USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
USART_Init(USART6, &USART_InitStructure);
USART_ITConfig(USART6, USART_IT_RXNE, ENABLE); // Cho phep ngat xay ra doi voi USART6
USART_Cmd(USART6, ENABLE); // Enable USART6
}
void NVIC_Config()
{
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); // Thiet lap nhom uu tien cho ngat la 1
NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn; // Kenh ngat la USART6_IRQn
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // Muc uu tien ngat bang 0
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // Thiet lap SubPriority cua ngat bang 0
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // Xac lap kenh ngat
NVIC_Init(&NVIC_InitStructure);
}
/*************************************************
Function: void USART6_Puts(char * str)
Description: USART6 Put string
Input: A string
Output:
Return:
*************************************************/
void USART6_Puts(char * str)
{
while (*str)
{
USART_SendData(USART6, *str++);
/* Loop until the end of transmission */
// Reference manual: when TXE is set, a frame of data transmission is completed
while (USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);
}
}

/*************************************************
Function: void USART6_IRQHandler(void)
Description: USART6 Interrupt request handler
Input:
Output:
Return:
*************************************************/
void USART6_IRQHandler(void)
{
// Neu xay ra ngat USART6
if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
{
// Nhan du lieu ve va gui di ngay
USART_SendData(USART6, USART_ReceiveData(USART6));
// Tat den LED o chan 12 cong D de bao hieu ket thuc truyen du lieu
GPIO_ResetBits(GPIOA, GPIO_Pin_6);
}
}