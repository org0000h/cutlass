/*
 * output.c
 *
 *  Created on: 2018/12/06
 *      Author: yazhou
 */
#define IN_LINUX
#ifdef IN_LINUX
#include <stdio.h>
void _putchar(char character){
    fputc(character,stdout);
    return;
}
#endif
