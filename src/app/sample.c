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
        LOG_INFO("%s",(char *)node->val);
    }

    list_iterator_destroy(it);
    list_destroy(langs);
//

//
    string_t * str = string_new_with_string_copy("hello");
    LOG_INFO("%s",string_get(str));
    string_append(str, "world");
    LOG_INFO("%s",string_get(str));
    if(string_prepend(str, "pre ") <0){
        LOG_INFO("error");
    }
    LOG_INFO("%s",string_get(str));
//
    LOG_INFO("log test");
    LOG_WARN("log test");
    LOG_ERR("log test");
    console_daemon_run();
	return 0;
}
