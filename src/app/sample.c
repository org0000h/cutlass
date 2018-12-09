/*
 * app.c
 *
 *  Created on: 2017/12/17
 *      Author: asia
 */

#include <stdio.h>
#include <stdlib.h>

#include "type_int.h"
//#include "ClassString.h"
#include "log.h"

#include "common.h"
#include "data_structre_list.h"
#include "console_api.h"
int main(){

//
//    list_t *langs = list_new();
//
//    list_rpush(langs, list_node_new("c"));
//    list_rpush(langs, list_node_new("js"));
//    list_rpush(langs, list_node_new("python"));
//
//    list_node_t *node;
//    list_iterator_t *it = list_iterator_new(langs, LIST_HEAD);
//    while ((node = list_iterator_next(it))) {
//        PRINT_LOG_INFO("%s",(char *)node->val);
//    }
//
//    list_iterator_destroy(it);
//    list_destroy(langs);
//

//
//    string_t * str = string_new_with_string_copy("hello");
//    PRINT_LOG_INFO("%s",string_get(str));
//    string_append(str, "world");
//    PRINT_LOG_INFO("%s",string_get(str));
//    if(string_prepend(str, "pre ") <0){
//        PRINT_LOG_INFO("error");
//    }
//    PRINT_LOG_INFO("%s",string_get(str));
//
    PRINT_LOG_INFO("log test");
    PRINT_LOG_WARN("log test");
    PRINT_LOG_ERR("log test");
    console_daemon_run();
	return 0;
}
