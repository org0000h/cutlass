/*
 * app.c
 *
 *  Created on: 2017/12/17
 *      Author: asia
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "log.h"

#include "common.h"
#include "list.h"
#include "buffer.h"
int main(){

    int aa1 = 1;
    int bb1 = 2;
    SWAP(aa1, bb1);
    printf("aa=%d,bb=%d\n",aa1, bb1);

//>>>>>>>>>>>>>>>>>>>> list >>>>>>>>>>>>>>>>>>>>>>>
    list_t *langs = list_new();

    list_node_t *c = list_rpush(langs, list_node_new("c"));
    list_node_t *js = list_rpush(langs, list_node_new("js"));
    list_node_t *ruby = list_rpush(langs, list_node_new("ruby"));

    list_node_t *node;
    list_iterator_t *it = list_iterator_new(langs, LIST_HEAD);
    while ((node = list_iterator_next(it))) {
      puts(node->val);
    }

    list_iterator_destroy(it);
    list_destroy(langs);
//<<<<<<<<<<<<<<<<<<<<<< list <<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>> string >>>>>>>>>>>>>>>>>>>
//    char *s = "hello";
//    buffer_t * str = buffer_new_with_string(s);
//    if(str == NULL){
//    	printf("NULL\n");
//    	return ;
//    }else {
//    	printf("not \n");
//    }
//    printf(" %s fdsa\n",str->data);
//    buffer_append(str, "world");
////    buffer_print(str);
//<<<<<<<<<<<<<<<<<<<<<< string <<<<<<<<<<<<<<<<<<<
	return 0;
}
