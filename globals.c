#include "globals.h"
#include "flash_utils.h"
#include <stdio.h>

/************************************************************************************
 * Ethercat PDOs SDOs
 */
rx_pdo_t    	rx_pdo;
tx_pdo_t    	tx_pdo;
uint8_t *       rxpdo = (uint8_t*)&rx_pdo;
uint8_t *       txpdo = (uint8_t*)&tx_pdo;

sdo_t	sdo = {
	.ram.bl_ver = "($)^($)"
};


void print_sdo(const ram_sdo_t *s) {

	DPRINT("sdo.ram.bl_ver=%s\n", s->bl_ver);
    DPRINT("sdo.ram.crc_app=%" PRIX32 "\n", s->crc_app);
    DPRINT("sdo.ram.crc_cal=%" PRIX32 "\n", s->crc_cal);
    printf("\n");
}


/************************************************************************************
 * FOE files
 */
foe_cfg_t 	gFOE_config = { 0, 0, 0 ,0 };
uint8_t		foe_buffer[0x400];


foe_file_cfg_t      gFOE_firmware_files[] = {
	{
		.name =					"soes_stm32.bin",
		.max_data = 			FLASH_APP_BSIZE, 	// sector size ?!?
		.dest_start_address =	FLASH_APP_ADDR, 	//
		.address_offset =		0,
		.filepass =				0xB032,
		.write_only_in_boot =	true,
		.write_function =		foe_write_flash,
		.read_function =		foe_read_flash,
		.on_foe_open = 			on_foe_open_cb,
		.on_foe_close = 		on_foe_close_cb,
	},
	{
		.name =					"params.bin",
		.max_data = 			FLASH_PARAM_BSIZE, 	// sector size ?!?
		.dest_start_address =	FLASH_PARAM_ADDR, 	//
		.address_offset =		0,
		.filepass =				0xA4A4,
	//	.write_function =		foe_write_flash,
	//	.read_function =		foe_read_flash,
	//	.on_foe_open = 			on_foe_open_cb,
	//	.on_foe_close = 		on_foe_close_cb,
	},
	{
		.name =					"calib.bin",
		.max_data = 			FLASH_CALIB_BSIZE, 	// sector size ?!?
		.dest_start_address =	FLASH_CALIB_ADDR, 	//
		.address_offset =		0,
		.filepass =				0xCA71,
		.write_function =		foe_write_cal_mat,
		.read_function =		foe_read_cal_mat,
		.on_foe_open = 			0,
		.on_foe_close = 		0,
	},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
