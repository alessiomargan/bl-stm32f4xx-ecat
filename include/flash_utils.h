#ifndef _FLASH_UTILS_H_
#define _FLASH_UTILS_H_

#include "stdbool.h"
#include "stm32f4xx_hal.h"

#define FLASH_BLDR_ADDR		0x8000000 // sector 0
#define FLASH_BLDR_SECTOR	FLASH_SECTOR_0
#define FLASH_BLDR_NSECTORS	3 // sectors 0 1 2
#define FLASH_BLDR_BSIZE	48*1024 // 0xC000

#define FLASH_APP_ADDR		0x8020000 // sector 5
#define FLASH_APP_SECTOR	FLASH_SECTOR_5
#define FLASH_APP_NSECTORS	3 // sector 5 6 7
#define FLASH_APP_BSIZE		384*1024 // 0x60000


#define FLASH_PARAM_ADDR	0x800C000 // sector 3
#define FLASH_PARAM_SECTOR	FLASH_SECTOR_3
#define FLASH_PARAM_NSECTORS	1
#define FLASH_PARAM_BSIZE	16*1024 // 0x4000

#define FLASH_CALIB_ADDR	0x8010000 // sector 4
#define FLASH_CALIB_SECTOR	FLASH_SECTOR_4
#define FLASH_CALIB_NSECTORS	1
#define FLASH_CALIB_BSIZE	64*1024 // 0x10000

uint32_t Calc_CRC(uint32_t addr, uint32_t length);

bool Write_flash(uint32_t flash_addr, void * src, size_t size);

int Write_Flash_W(uint32_t flash_addr, uint32_t* src, size_t size);
int Erase_Flash_StartAddr(uint32_t flash_addr);

#endif
