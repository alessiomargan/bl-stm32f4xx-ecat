#ifndef __GLOBALS_H__
#define __GLOBALS_H__

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <cc.h>

#include <soes/esc_foe.h>

#define FLASH_SIGN_VALID		0xCAFE
#define FLASH_SIGN_DEFAULT		0xDEFA

#define PACKED	__attribute__((__packed__))


typedef struct {
	// empty
} PACKED tx_pdo_t;

typedef struct {
	// empty
} PACKED rx_pdo_t;

typedef struct {
    // 0x8001 ram param
    char 		bl_ver[8];
	uint16_t 	ctrl_cmd;
	uint16_t 	ctrl_cmd_ack;
	uint16_t 	flash_cmd;
	uint16_t 	flash_cmd_ack;
	uint32_t 	crc_app;
	uint32_t 	crc_cal;
} PACKED ram_sdo_t;

typedef struct {
    //flash_sdo_t	flash;
    ram_sdo_t	ram;
} PACKED sdo_t;


extern tx_pdo_t 			tx_pdo;
extern rx_pdo_t 			rx_pdo;
extern uint8_t *            rxpdo;
extern uint8_t *            txpdo;
extern sdo_t 				sdo;
//extern const flash_sdo_t	dflt_flash_sdo;
//extern const flash_sdo_t	flash_sdo;

extern foe_cfg_t 	gFOE_config;
extern uint8_t		foe_buffer[0x400];
extern foe_file_cfg_t	gFOE_firmware_files[];

void print_sdo(const ram_sdo_t *);

uint32_t foe_write_flash(foe_file_cfg_t *, uint8_t * data, size_t length);
uint32_t foe_read_flash(foe_file_cfg_t *, uint8_t * data, size_t length);
uint32_t on_foe_open_cb( uint8_t );
uint32_t on_foe_close_cb( void );
uint32_t foe_write_cal_mat( foe_file_cfg_t *, uint8_t * data, size_t length );
uint32_t foe_read_cal_mat ( foe_file_cfg_t *, uint8_t * data, size_t length );

#endif
