/*
 * string.h
 *
 *  Created on: 2018/10/10
 *      Author: yazhou
 */
#include <sys/types.h>


typedef struct _string string_t;

string_t *
string_new_with_size(size_t n);

string_t *
string_new_with_string_copy(char *str);

void string_print(string_t *self);

char *string_get(string_t *self);

size_t
string_length(string_t *self);

void
string_free(string_t *self);

void
string_free(string_t *self);

int
string_prepend(string_t *self, char *str);

int
string_append(string_t *self, const char *str);

int
string_appendf(string_t *self, const char *format, ...);

int
string_append_n(string_t *self, const char *str, size_t len);

int
string_equals(string_t *self, string_t *other);

ssize_t
string_indexof(string_t *self, char *str);

string_t *
string_slice(string_t *self, size_t from, ssize_t to);

ssize_t
string_compact(string_t *self);

int
string_resize(string_t *self, size_t n);
