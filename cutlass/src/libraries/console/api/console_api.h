#ifndef CONSOLE_API_H
#define CONSOLE_API_H

#include "console_config.h"
typedef struct _microrl_t *microrl_t;
typedef void (*SIGINTF)(void);
 microrl_t new_microrl(void);

// init internal data, calls once at start up
void microrl_init (microrl_t   pThis, void (*print)(const char*));

// set echo mode (true/false), using for disabling echo for password input
// echo mode will enabled after user press Enter.
void microrl_set_echo (int);

// set pointer to callback complition func, that called when user press 'Tab'
// callback func description:
//   param: argc - argument count, argv - pointer array to token string
//   must return NULL-terminated string, contain complite variant splitted by 'Whitespace'
//   If complite token found, it's must contain only one token to be complitted
//   Empty string if complite not found, and multiple string if there are some token
void microrl_set_complete_callback (microrl_t   pThis, char ** (*get_completion)(int, const char* const*));

// pointer to callback func, that called when user press 'Enter'
// execute func param: argc - argument count, argv - pointer array to token string
void microrl_set_execute_callback (microrl_t   pThis, int (*execute)(int, const char* const*));

// set callback for Ctrl+C terminal signal
#ifdef _USE_CTLR_C
void microrl_set_sigint_callback (microrl_t   pThis, SIGINTF sigintf);
#endif

// insert char to cmdline (for example call in usart RX interrupt)
void microrl_insert_char (microrl_t   pThis, int ch);

void console_daemon_run(void);

#endif

