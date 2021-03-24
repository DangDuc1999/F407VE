
#include "Flash.h"
/**
* @brief Gets the sector of a given address
* @param None
* @retval The sector of a given address
*/
uint32_t GetSector(uint32_t Address)
{
uint32_t sector = 0;
if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
{
sector = FLASH_Sector_0;
}
else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
{
sector = FLASH_Sector_1;
} 
else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
{
sector = FLASH_Sector_2;
}
else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
{
sector = FLASH_Sector_3;
}
else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
{
sector = FLASH_Sector_4;
}
else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
{
sector = FLASH_Sector_5;
}
else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
{
sector = FLASH_Sector_6;
}
else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
{
sector = FLASH_Sector_7;
}
else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
{
sector = FLASH_Sector_8;
}
else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
{
sector = FLASH_Sector_9;
}
else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
{
sector = FLASH_Sector_10;
}
else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
{
sector = FLASH_Sector_11;
}
return sector;
}