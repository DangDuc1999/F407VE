#ifndef _FLASH_H_
#define _FLASH_H_
#include "main.h"
#include "stm32f4xx_flash.h"
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
/* Bat dau dia chi vung nho Flash danh cho nguoi dung */
#define FLASH_USER_START_ADDR ADDR_FLASH_SECTOR_2
/* Ket thuc dia chi vung nho Flash danh cho nguoi dung */
#define FLASH_USER_END_ADDR ADDR_FLASH_SECTOR_5
/* Dia chi co so cua cac Flash sectors */
/* Dia chi co so cua Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_0 ((uint32_t)0x08000000)
/* Dia chi co so cua Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1 ((uint32_t)0x08004000)
/* Dia chi co so cua Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2 ((uint32_t)0x08008000)
/* Dia chi co so cua Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3 ((uint32_t)0x0800C000)
/* Dia chi co so cua Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_4 ((uint32_t)0x08010000)
/* Dia chi co so cua Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_5 ((uint32_t)0x08020000)
/* Dia chi co so cua Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6 ((uint32_t)0x08040000)
/* Dia chi co so cua Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7 ((uint32_t)0x08060000)
/* Dia chi co so cua Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8 ((uint32_t)0x08080000)
/* Dia chi co so cua Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9 ((uint32_t)0x080A0000)
/* Dia chi co so cua Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x080C0000)
/* Dia chi co so cua Sector 11, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x080E0000)
#define DATA_32 ((uint32_t)0x12345678)
/* Private macro -------------------------------------------------------------*/

uint32_t GetSector(uint32_t Address);

#endif