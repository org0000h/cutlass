/*
 * string.c
 *
 *  Created on: 2018/10/10
 *      Author: yazhou
 */


/*
 * string struct.
 */

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#
#include "ClassString.h"

struct _string{
  size_t len;
  char *alloc;
  char *data;
};
/*
 * Compute the nearest multiple of `a` from `b`.
 */

#define nearest_multiple_of(a, b) \
  (((b) + ((a) - 1)) & ~((a) - 1))

/*
 * Allocate a new string with `n` bytes.
 */

string_t *
string_new_with_size(size_t n) {
  string_t *self = malloc(sizeof(string_t));
  if (!self) return NULL;
  self->len = n;
  self->data = self->alloc = calloc(n + 1, 1);
  return self;
}
/*
 * Allocate a new string with a copy of `str`.
 */

string_t *
string_new_with_string_copy(char *str) {
  size_t len = strlen(str);
  string_t *self = string_new_with_size(len);
  if (!self) return NULL;
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}

void string_print(string_t *self){
    if(self == NULL){
        printf("string is NULL!\n");
    }
    printf("[string_print]: %s\n",self->data);
}
char *string_get(string_t *self){
    if(self == NULL){
        printf("string is NULL!\n");
    }
    return self->data;
}
/*
 * Free the string.
 */

void
string_free(string_t *self) {
  free(self->alloc);
  free(self);
}

/*
 * Prepend `str` to `self` and return 0 on success, -1 on failure.
 */

int
string_prepend(string_t *self, char *str) {
  size_t len = strlen(str);
  size_t prev = strlen(self->data);
  size_t needed = len + prev;

  // enough space
  if (self->len > needed) goto move;

  // resize
  int ret = string_resize(self, needed);
  if (-1 == ret) return -1;

  // move
  move:
  memmove(self->data + len, self->data, self->len + 1);
  memcpy(self->data, str, len);

  return 0;
}
/*
 * Append `str` to `self` and return 0 on success, -1 on failure.
 */

int
string_append(string_t *self, const char *str) {
  return string_append_n(self, str, strlen(str));
}

/*
 * Append the first `len` bytes from `str` to `self` and
 * return 0 on success, -1 on failure.
 */
int
string_append_n(string_t *self, const char *str, size_t len) {
  size_t prev = strlen(self->data);
  size_t needed = len + prev;

  // enough space
  if (self->len > needed) {
    strncat(self->data, str, len);
    return 0;
  }

  // resize
  int ret = string_resize(self, needed);
  if (-1 == ret) return -1;
  strncat(self->data, str, len);

  return 0;
}
/*
 * Return a new string based on the `from..to` slice of `buf`,
 * or NULL on error.
 */

string_t *
string_slice(string_t *buf, size_t from, ssize_t to) {
  size_t len = strlen(buf->data);

  // bad range
  if (to < from) return NULL;

  // relative to end
  if (to < 0) to = len - ~to;

  // cap end
  if (to > len) to = len;

  size_t n = to - from;
  string_t *self = string_new_with_size(n);
  memcpy(self->data, buf->data + from, n);
  return self;
}

/*
 * Return 1 if the strings contain equivalent data.
 */

int
string_equals(string_t *self, string_t *other) {
  return 0 == strcmp(self->data, other->data);
}

/*
 * Return the index of the substring `str`, or -1 on failure.
 */

ssize_t
string_indexof(string_t *self, char *str) {
  char *sub = strstr(self->data, str);
  if (!sub) return -1;
  return sub - self->data;
}

/*
 * Trim leading whitespace.
 */

void
string_trim_left(string_t *self) {
  int c;
  while ((c = *self->data) && isspace(c)) {
    ++self->data;
  }
}

/*
 * Trim trailing whitespace.
 */

void
string_trim_right(string_t *self) {
  int c;
  size_t i = string_length(self) - 1;
  while ((c = self->data[i]) && isspace(c)) {
    self->data[i--] = 0;
  }
}

/*
 * Trim trailing and leading whitespace.
 */

void
string_trim(string_t *self) {
  string_trim_left(self);
  string_trim_right(self);
}

/*
 * Resize to hold `n` bytes.
 */

int
string_resize(string_t *self, size_t n) {
  n = nearest_multiple_of(1024, n);
  self->len = n;
  self->alloc = self->data = realloc(self->alloc, n + 1);
  if (!self->alloc) return -1;
  self->alloc[n] = '\0';
  return 0;
}
/*
 * Return string length.
 */

size_t
string_length(string_t *self) {
  return strlen(self->data);
}
