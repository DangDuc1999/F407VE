#include "main.h"
#include "Flash.h"
void DeleteSector();
void CheckSector();
void WriteData();
/* Private variables ---------------------------------------------------------*/
uint32_t StartSector = 0, EndSector = 0, Address = 0, i = 0 ;
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0 ;
int main(void)
{
  SystemInit();
  FLASH_Unlock();         // STD
  DeleteSector();
  WriteData();
  FLASH_Lock();           // STD
  CheckSector();

  printf("DataS0 : %d \n",GetSector(ADDR_FLASH_SECTOR_0));
  printf("DataS1 : %d \n",GetSector(ADDR_FLASH_SECTOR_1));
  printf("DataS2 : %d \n",GetSector(ADDR_FLASH_SECTOR_2));
  printf("DataS3 : %d \n",GetSector(ADDR_FLASH_SECTOR_3));
  printf("DataS4 : %d \n",GetSector(ADDR_FLASH_SECTOR_4));
  printf("DataS5 : %d \n",GetSector(ADDR_FLASH_SECTOR_5));
  printf("DataS6 : %d \n",GetSector(ADDR_FLASH_SECTOR_6));
while (1)     //  loop
{
  

}
} // end main

void DeleteSector()
{
  /* Xoa vung nho Flash danh cho nguoi dung
(vung nho nam giua FLASH_USER_START_ADDR va FLASH_USER_END_ADDR) */
/* Xoa pending flags (neu co) */
FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
/* Lay number cua Sector bat dau va Sector ket thuc */
StartSector = GetSector(FLASH_USER_START_ADDR);
EndSector = GetSector(FLASH_USER_END_ADDR);
for (i = StartSector; i < EndSector; i += 8)            // Xoa Sector
{
/* Hieu dien the nam trong khoang [2.7V den 3.6V] */
if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE)  // STD
{
/* Co loi khi xoa sector. Nguoi dung co the them code vao day de xu ly loi */
while (1)
{ }
}
}
}
void CheckSector()
{
  /* Kiem tra xem viec ghi vao Flash co chinh xac khong
MemoryProgramStatus = 0: du lieu duoc ghi chinh xac
MemoryProgramStatus != 0: so word bi ghi khong chinh xac */
Address = FLASH_USER_START_ADDR;
MemoryProgramStatus = 0x0;
while (Address < FLASH_USER_END_ADDR)
{
data32 = *(__IO uint32_t*)Address;
if (data32 != DATA_32)
{
MemoryProgramStatus++;
}
Address = Address + 4;
}// end check
printf("So word sai: %d\n",MemoryProgramStatus);
}
void WriteData()
{
  /*if (FLASH_ProgramWord(ADDR_FLASH_SECTOR_2, 99) == FLASH_COMPLETE) // STD
{
  FLASH_ProgramWord(ADDR_FLASH_SECTOR_2, 99);
}
else
{
// Co loi khi ghi du lieu. Nguoi dung co the them code vao day de xu ly loi 
while (1)
{ }
} // End write data
*/
  FLASH_ProgramWord(ADDR_FLASH_SECTOR_2, 99);
}