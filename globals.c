#include <stdio.h>

#include "globals.h"
#include "flash_utils.h"
#include "build_info.h"

/************************************************************************************
 * Ethercat PDOs SDOs
 */
rx_pdo_t    	rx_pdo;
tx_pdo_t    	tx_pdo;
uint8_t *       rxpdo = (uint8_t*)&rx_pdo;
uint8_t *       txpdo = (uint8_t*)&tx_pdo;

sdo_t	sdo = {
	.ram.bl_ver = BUILD_SHORT_TS
};


void print_sdo(const ram_sdo_t *s) {

	DPRINT("sdo.ram.bl_ver=%s\n", s->bl_ver);
    DPRINT("sdo.ram.crc_app=%" PRIX32 "\n", s->crc_app);
    DPRINT("sdo.ram.crc_cal=%" PRIX32 "\n", s->crc_cal);
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
		.max_data = 			FLASH_PAR_BSIZE, 	// sector size ?!?
		.dest_start_address =	FLASH_PAR_ADDR, 	//
		.address_offset =		0,
		.filepass =				0xA4A4,
	//	.write_function =		foe_write_flash,
	//	.read_function =		foe_read_flash,
	//	.on_foe_open = 			on_foe_open_cb,
	//	.on_foe_close = 		on_foe_close_cb,
	},
	{
		.name =					"calib.bin",
		.max_data = 			FLASH_CAL_BSIZE, 	// sector size ?!?
		.dest_start_address =	FLASH_CAL_ADDR, 	//
		.address_offset =		0,
		.filepass =				0xCA71,
		.write_function =		foe_write_cal_mat,
		.read_function =		foe_read_cal_mat,
		.on_foe_open = 			0,
		.on_foe_close = 		0,
	},
	{ 0 }
};

/*
 *
 */
const uint8_t git_hash[] = GIT_HASH;
const uint8_t git_branch[] = GIT_BRANCH;
const uint8_t git_tag[] = GIT_TAG;
const uint8_t build_ts[] = BUILD_TIMESTAMP;
const uint8_t build_short_ts[] = BUILD_SHORT_TS;

void print_build_info(void) {

	printf("\n");
	printf("Build Timestamp: %s\n", BUILD_TIMESTAMP);
	printf("Build short Timestamp: %s\n", BUILD_SHORT_TS);
	printf("Git Hash: %s\n", GIT_HASH);
    printf("Git Commit Hash: %s\n", GIT_COMMIT_HASH);
    printf("Git Branch: %s\n", GIT_BRANCH);
    printf("Git Tag: %s\n", GIT_TAG);
    printf("Repository Dirty: %d\n", GIT_DIRTY);
    printf("Git Repository URL: %s\n", GIT_REPO_URL);
    printf("Build Host: %s\n", BUILD_HOST);
    printf("Build User: %s\n", BUILD_USER);
    printf("Build OS: %s\n", BUILD_OS);
    printf("\n");

}

