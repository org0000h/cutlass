/*
 * app.c
 *
 *  Created on: 2017/12/17
 *      Author: asia
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "ClassString.h"
#include "log.h"

#include "common.h"
#include "list.h"
#include "console_api.h"
int main(){

//
    list_t *langs = list_new();

    list_rpush(langs, list_node_new("c"));
    list_rpush(langs, list_node_new("js"));
    list_rpush(langs, list_node_new("python"));

    list_node_t *node;
    list_iterator_t *it = list_iterator_new(langs, LIST_HEAD);
    while ((node = list_iterator_next(it))) {
      puts(node->val);
    }

    list_iterator_destroy(it);
    list_destroy(langs);
//

//
    string_t * str = string_new_with_string_copy("hello");
    printf("%s\n",string_get(str));
    string_append(str, "world");
    printf("%s\n",string_get(str));
    if(string_prepend(str, "pre ") <0){
        printf("error\n");
    }
    printf("%s\n",string_get(str));
//

    console_daemon_run();
	return 0;
}