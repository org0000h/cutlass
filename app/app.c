/*
 * app.c
 *
 *  Created on: 2017年12月17日
 *      Author: asia
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "log.h"

#include "common.h"

int main(){

    int aa1 = 1;
    int bb1 = 2;
    SWAP(aa1, bb1);
    printf("aa=%d,bb=%d\n",aa1, bb1);

	return 0;
}
