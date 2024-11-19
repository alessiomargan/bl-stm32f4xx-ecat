/*
 * foe_utils.c
 *
 *  Created on: Oct 19, 2024
 *      Author: amargan
 */
#include <soes/esc_foe.h>
#include <globals.h>
#include <flash_utils.h>

uint32_t foe_write_flash(foe_file_cfg_t * wr_cfg, uint8_t * data, size_t length) {

	uint32_t bytestowrite = gFOE_config.buffer_size;
    uint32_t ui32FlashAddr = wr_cfg->address_offset + wr_cfg->dest_start_address;
    DPRINT("%s FlashAddr 0x%04X with %d bytes\n", __FUNCTION__, ui32FlashAddr, bytestowrite);
    // HAL_OK = 0
    return Write_Flash_W(ui32FlashAddr, (void*)data, bytestowrite);
}

uint32_t foe_read_flash(foe_file_cfg_t * self, uint8_t * data, size_t length) {

	return 1;
}

uint32_t on_foe_open_cb(uint8_t op) {
	// 0 OK ==> HAL_OK
	uint32_t ret = Erase_Flash_StartAddr(FLASH_APP_ADDR);
	DPRINT("%s erase sector 0x%04X = %d\n", __FUNCTION__, FLASH_APP_ADDR, ret);
	return ret;
}

uint32_t on_foe_close_cb( void ) {
	// 0 OK ==> HAL_OK
	uint32_t crc_app = 0xDEADBEEF;
	uint32_t crc_addr = FLASH_APP_ADDR+FLASH_APP_BSIZE-4;
	crc_app = Calc_CRC(FLASH_APP_ADDR, (FLASH_APP_BSIZE/4)-1);
	uint32_t ret = Write_Flash_W(crc_addr, (void*)&crc_app, sizeof(crc_app));
	if (ret == HAL_OK) {
		sdo.ram.crc_app = *(uint32_t*)(FLASH_APP_ADDR+FLASH_APP_BSIZE-4);
		sdo.ram.crc_cal = crc_app;
		DPRINT("%s crc_addr 0x%04X crc_app 0x%04X\n", __FUNCTION__, crc_addr, sdo.ram.crc_app);
	} else {
		DPRINT("%s FAIL write at crc_addr 0x%04X crc_app 0x%04X\n", __FUNCTION__, crc_addr, sdo.ram.crc_app);
	}

	return ret;
}

uint32_t foe_write_cal_mat( foe_file_cfg_t * writefile_cfg, uint8_t * data, size_t length ) {
	return 1;
}

uint32_t foe_read_cal_mat ( foe_file_cfg_t * writefile_cfg, uint8_t * data, size_t length ) {
	return 1;
}
