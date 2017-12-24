/*
 * app.c
 *
 *  Created on: 2017年12月17日
 *      Author: asia
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "except.h"
#include "assert.h"
#include "mem.h"
#include "array.h"
#include "log.h"
#include "arena.h"
#include "stack.h"

Except_T Failed1 = { "e1"};
Except_T Failed2 = { "e2"};
Except_T Failed3 = { "e3"};
Except_T Failed4 = { "e4"};

int main(){
	TRY
	{
		/* dynamic memory */
		int *a;
		NEW0(a);
		*a = 2;
		PRINT_LOG_INFO("a = %d",*a);
		FREE(a);
		Arena_T m = Arena_new();
		a = M_alloc(m, sizeof(a));
		Arena_free(m);

		/*  arry  */
		Array_T arry = Array_new(10,sizeof(int));
		int a0 =9;
		Array_put(arry,0,&a0);
		int *bb = Array_get(arry,0);
		PRINT_LOG_INFO("bb = %d", *bb);
        
        /* stack  */
		Stack_T stack = Stack_new();
		Stack_push(stack, &a0);
		int *aa = (int *)Stack_pop(stack);
		PRINT_LOG_INFO("aa = %d", *aa);
		Stack_free(&stack);
		/* except */
		TRY
/*			foo( key);*/
		EXCEPT(Failed1)
			PRINT_LOG_ERR("except1");
		EXCEPT(Failed2)
			PRINT_LOG_ERR("except2");
		EXCEPT(Failed3)
			PRINT_LOG_ERR("except3");
		ELSE
			PRINT_LOG_ERR("except4");
		FINALLY
			PRINT_LOG_ERR("finally");
		END_TRY
	}
	ELSE
		PRINT_LOG_ERR("An internal error has occurred for this is no recovery.");
		RERAISE;
	END_TRY;
	return 0;
}
