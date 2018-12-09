/*
 * output.c
 *
 *  Created on: 2018/12/06
 *      Author: yazhou
 */
//#define IN_LINUX
//#define IN_STM32
#ifdef IN_LINUX
#include <stdio.h>
void _putchar(char character){
    fputc(character,stdout);
    return;
}
#endif

#ifdef IN_STM32
#include "usart.h"
extern UART_HandleTypeDef huart1;
void _putchar(char character){
	HAL_UART_Transmit(&huart1, (uint8_t*)&character, 1, 100);
}
#endif
