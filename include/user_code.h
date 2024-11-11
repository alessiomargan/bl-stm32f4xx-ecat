/*
 * user_code.h
 *
 *  Created on: Nov 6, 2024
 *      Author: amargan
 */

#ifndef INC_USER_CODE_H_
#define INC_USER_CODE_H_

#include "main.h"

#define DBG_1_ON	HAL_GPIO_WritePin(DBG_1_GPIO_Port, DBG_1_Pin, GPIO_PIN_SET)
#define DBG_1_OFF	HAL_GPIO_WritePin(DBG_1_GPIO_Port, DBG_1_Pin, GPIO_PIN_RESET)
#define DBG_2_ON	HAL_GPIO_WritePin(DBG_2_GPIO_Port, DBG_2_Pin, GPIO_PIN_SET)
#define DBG_2_OFF	HAL_GPIO_WritePin(DBG_2_GPIO_Port, DBG_2_Pin, GPIO_PIN_RESET)
#define LED_1_TGL	HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin)
#define LED_1_ON 	HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_SET)
#define LED_1_OFF 	HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, GPIO_PIN_RESET)
#define LED_2_TGL	HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin)
#define LED_2_ON 	HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_SET)
#define LED_2_OFF 	HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, GPIO_PIN_RESET)

void user_code_init(void);
void user_code_loop(void);

#endif /* INC_USER_CODE_H_ */
