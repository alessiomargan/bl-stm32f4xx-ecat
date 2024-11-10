/*
 * user_code.c
 *
 *  Created on: Nov 6, 2024
 *      Author: amargan
 */
#include <soes/esc.h>
#include <soes/ecat_slv.h>
#include <globals.h>
//#include <params.h>
#include <flash_utils.h>
#include <user_code.h>

#include <stdio.h>
#include <main.h>
#include <stm32f4xx_hal.h>

extern uint32_t ESC_SYNCactivation(void);
extern esc_cfg_t config;
//
uint32_t uid[3];
// morse led
const char *message = "boot  ";
extern void update_led(const char *);

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART1 and Loop until the end of transmission */
  HAL_UART_Transmit(&printf_uart, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if (GPIO_Pin == ECAT_IRQ_Pin) {
		DBG_1_ON;
		ecat_slv();
		DBG_1_OFF;
	} else if (GPIO_Pin == BTN_1_Pin) {

	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM6) {
		HAL_IncTick();
	}
	if (htim->Instance == TIM7) {
		DBG_2_ON;
		if ( ! ESC_SYNCactivation() ) {
			ecat_slv();
		}
		DBG_2_OFF;
	}
}

static inline void read_UID(void) {

	uid[0] = *(uint32_t *)UID_BASE;
	uid[1] = *(uint32_t *)(UID_BASE + 4);
	uid[2] = *(uint32_t *)(UID_BASE + 8);
}

static inline uint32_t read_user_RAM(void) {

	uint32_t value;
	ESC_read(0xF80, &value, sizeof(value));
	DPRINT("user_RAM 0x%X\n", value);
	return value;
}
/*
 * return > 0 will jump to app
 */
static inline uint8_t test_jump2app(void) {

	uint8_t ret = 0;
	uint8_t sw1 = 0;
	uint8_t ecat_boot = 0;
	uint8_t user_ram = 0;
	uint8_t crc_ok = sdo.ram.crc_cal == sdo.ram.crc_app;
	// poll button ... 0 pressed
	// sw1 == 1 ==> pressed
	//sw1 = (~MAP_GPIO_getInputPinValue(PORT_SWITCH, SW1_PIN)) & 0x1;
#ifdef HAVE_BOOT_PIN
	ecat_boot = MAP_GPIO_getInputPinValue(PORT_ECAT_BOOT, PIN_ECAT_BOOT);
#else
	user_ram = (read_user_RAM() == 0xB007B007);
#endif
    ret = (!(sw1 || ecat_boot || user_ram)) && crc_ok;
    DPRINT("%s : %d = (not( %d || %d || %d )) && %d\n",
           __FUNCTION__, ret, sw1, ecat_boot, user_ram, crc_ok);

	return ret;
}

static inline void jump2app(void) {

	/* Set system control register SCR->VTOR  */
	SCB->VTOR = FLASH_APP_ADDR;
	//__disable_irq();
	uint32_t JumpAddress = *(__IO uint32_t*) (FLASH_APP_ADDR + 4);
	__set_MSP(*(__IO uint32_t*) FLASH_APP_ADDR);
	((void (*)()) JumpAddress)();
}

static inline void try_boot(void) {

    if ( test_jump2app() ) {
        jump2app();
    }
}

void user_code_init(void) {

	read_UID();
	DPRINT("Start =====>\n");
	sdo.ram.crc_cal = Calc_CRC(FLASH_APP_ADDR, (FLASH_APP_BSIZE/4)-1);
	sdo.ram.crc_app = *(uint32_t*)(FLASH_APP_ADDR+FLASH_APP_BSIZE-4);
	print_sdo(&sdo.ram);
	/* Init soes */
	ecat_slv_init(&config);
	/* try boot application */
	try_boot();
	/* timer initialization with interrupt mode */
	HAL_TIM_Base_Start_IT(&htim7);

}

void user_code_loop(void) {

	HAL_Delay(100);
	update_led(message);
	TOGLLE_GRN;

}
