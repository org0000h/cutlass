/*
Platform independent interface for implementing some specific function
for AVR, linux PC or ARM
*/
#include "console_config.h"
#include "stdint.h"
#include <string.h>

#ifdef ON_STM32
#include "usart.h"

// print to stream callback
void print (const char * str){
    HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str) + 1, 100);
}

// get_char from stream
char get_char (void){
     uint8_t r[100] = {0};
     HAL_UART_Receive(&huart1, r, 1, 100);
    return r[0];
}
// definition commands word
#define _CMD_HELP  "help"
#define _CMD_CLEAR "clear"
#define _CMD_LIST  "list"
#define _CMD_LISP  "lisp" // for demonstration completion on 'l + <TAB>'
#define _CMD_NAME  "name"
#define _CMD_VER   "version"
// sub commands for version command
    #define _SCMD_MRL  "microrl"
    #define _SCMD_DEMO "demo"

#define _NUM_OF_CMD 6
#define _NUM_OF_VER_SCMD 2
#define _NUN_OF_EVENT 5
//available  commands
char * keyworld [] = {_CMD_HELP, _CMD_CLEAR, _CMD_LIST, _CMD_NAME, _CMD_VER, _CMD_LISP};
// version subcommands
char * ver_keyworld [] = {_SCMD_MRL, _SCMD_DEMO};

// array for comletion
char * compl_world [_NUM_OF_CMD + 1];

// 'name' var for store some string
#define _NAME_LEN 8
char name [_NAME_LEN];
int val;

typedef struct event_handle{
	const char *event;
	void  (*handle)(int,const char * const * );
}EVENT_HANDLE;


//*****************************************************************************
// completion callback
char ** complet (int argc, const char * const * argv){
    int j = 0;

        compl_world [0] = NULL;

        // if there is token in cmdline
        if (argc == 1) {
            // get last entered token
            char * bit = (char*)argv [argc-1];
            // iterate through our available token and match it
            for (int i = 0; i < _NUM_OF_CMD; i++) {
                // if token is matched (text is part of our token starting from 0 char)
                if (strstr(keyworld [i], bit) == keyworld [i]) {
                    // add it to completion set
                    compl_world [j++] = keyworld [i];
                }
            }
        }   else if ((argc > 1) && (strcmp (argv[0], _CMD_VER)==0)) { // if command needs subcommands
            // iterate through subcommand for command _CMD_VER array
            for (int i = 0; i < _NUM_OF_VER_SCMD; i++) {
                if (strstr (ver_keyworld [i], argv [argc-1]) == ver_keyworld [i]) {
                    compl_world [j++] = ver_keyworld [i];
                }
            }
        } else { // if there is no token in cmdline, just print all available token
            for (; j < _NUM_OF_CMD; j++) {
                compl_world[j] = keyworld [j];
            }
        }

        // note! last ptr in array always must be NULL!!!
        compl_world [j] = NULL;
        // return set of variants
        return compl_world;
}

// ctrl+c callback
void sigint (void){
    print ("^C catched! exit console\n\r");
}

void command_execute_help (int argc, const char * const * argv)
{
    print ("microrl library based shell v 1.0\n\r");
    print ("Use TAB key for completion\n\rCommand:\n\r");
    print ("\tversion {microrl | demo} - print version of microrl lib or version of this demo src\n\r");
    print ("\thelp  - this message\n\r");
    print ("\tclear - clear screen\n\r");
    print ("\tlist  - list all commands in tree\n\r");
    print ("\tname [string] - print 'name' value if no 'string', set name value to 'string' if 'string' present\n\r");
    print ("\tlisp - dummy command for demonstation auto-completion, while inputed 'l+<TAB>'\n\r");
}
void command_execute_list(int argc, const char * const * argv){
    print ("available command:\n");// print all command per line
    for (int i = 0; i < _NUM_OF_CMD; i++) {
        print ("\t");
        print (keyworld[i]);
        print ("\n\r");
    }
}

void command_execute_version(int argc, const char * const * argv){
	 int i = 0;
    if (++i < argc) {
        if (strcmp (argv[i], _SCMD_DEMO) == 0) {
            print ("demo v 1.0\n\r");
        } else if (strcmp (argv[i], _SCMD_MRL) == 0) {
            print ("microrl v 1.2\n\r");
        } else {
            print ((char*)argv[i]);
            print (" wrong argument, see help\n\r");
        }
    } else {
        print ("version needs 1 parametr, see help\n\r");
    }
}
void command_execute_name(int argc, const char * const * argv){
	int i = 0;
    if ((++i) < argc) { // if value preset
        if (strlen (argv[i]) < _NAME_LEN) {
            strcpy (name, argv[i]);
        } else {
            print ("name value too long!\n\r");
        }
    } else {
        print (name);
        print ("\n\r");
    }
}
void command_execute_clear(int argc, const char * const * argv){
    print ("\033[2J");    // ESC seq for clear entire screen
    print ("\033[H");     // ESC seq for move cursor at left-top corner
}
EVENT_HANDLE event_handle_table[_NUN_OF_EVENT] = {
		{_CMD_HELP,command_execute_help},
		{_CMD_CLEAR,command_execute_clear},
		{_CMD_LIST,command_execute_list},
		{_CMD_NAME,command_execute_name},
		{_CMD_VER,command_execute_version},

};
//
int execute (int argc, const char * const * argv){
	int i = 0;
	for(i = 0; i < _NUN_OF_EVENT; i++){
		if (strcmp (argv[0], event_handle_table[i].event) == 0) {
			event_handle_table[i].handle(argc,argv);
			return 0;
		}
	}
	print ("command: '");
	print ((char*)argv[0]);
	print ("' Not found.\n\r");
	return -1;
}

#endif


#ifdef ON_LINUX
#include <termios.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

//*****************************************************************************
// print callback for microrl library
void print (const char * str)
{
    fprintf (stdout, "%s", str);
}


//*****************************************************************************
// get char user pressed, no waiting Enter input
char get_char (void)
{
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}


// definition commands word
#define _CMD_HELP  "help"
#define _CMD_CLEAR "clear"
#define _CMD_LIST  "list"
#define _CMD_LISP  "lisp" // for demonstration completion on 'l + <TAB>'
#define _CMD_NAME  "name"
#define _CMD_VER   "version"
// sub commands for version command
    #define _SCMD_MRL  "microrl"
    #define _SCMD_DEMO "demo"

#define _NUM_OF_CMD 6
#define _NUM_OF_VER_SCMD 2

//available  commands
char * keyworld [] = {_CMD_HELP, _CMD_CLEAR, _CMD_LIST, _CMD_NAME, _CMD_VER, _CMD_LISP};
// version subcommands
char * ver_keyworld [] = {_SCMD_MRL, _SCMD_DEMO};

// array for comletion
char * compl_world [_NUM_OF_CMD + 1];

// 'name' var for store some string
#define _NAME_LEN 8
char name [_NAME_LEN];
int val;


//*****************************************************************************
void command_execute_help ()
{
    print ("Use TAB key for completion\n\rCommand:\n\r");
    print ("\tversion {microrl | demo} - print version of microrl lib or version of this demo src\n\r");
    print ("\thelp  - this message\n\r");
    print ("\tclear - clear screen\n\r");
    print ("\tlist  - list all commands in tree\n\r");
    print ("\tname [string] - print 'name' value if no 'string', set name value to 'string' if 'string' present\n\r");
    print ("\tlisp - dummy command for demonstation auto-completion, while inputed 'l+<TAB>'\n\r");
}

//*****************************************************************************
// execute callback for microrl library
// do what you want here, but don't write to argv!!! read only!!
int execute (int argc, const char * const * argv)
{
    int i = 0;
    // just iterate through argv word and compare it with your commands
    while (i < argc) {
        if (strcmp (argv[i], _CMD_HELP) == 0) {
            print ("microrl library based shell v 1.0\n\r");
            command_execute_help ();        // print help
        } else if (strcmp (argv[i], _CMD_NAME) == 0) {
            if ((++i) < argc) { // if value preset
                if (strlen (argv[i]) < _NAME_LEN) {
                    strcpy (name, argv[i]);
                } else {
                    print ("name value too long!\n\r");
                }
            } else {
                print (name);
                print ("\n\r");
            }
        } else if (strcmp (argv[i], _CMD_VER) == 0) {
            if (++i < argc) {
                if (strcmp (argv[i], _SCMD_DEMO) == 0) {
                    print ("demo v 1.0\n\r");
                } else if (strcmp (argv[i], _SCMD_MRL) == 0) {
                    print ("microrl v 1.2\n\r");
                } else {
                    print ((char*)argv[i]);
                    print (" wrong argument, see help\n\r");
                }
            } else {
                print ("version needs 1 parametr, see help\n\r");
            }
        } else if (strcmp (argv[i], _CMD_CLEAR) == 0) {
            print ("\033[2J");    // ESC seq for clear entire screen
            print ("\033[H");     // ESC seq for move cursor at left-top corner
        } else if (strcmp (argv[i], _CMD_LIST) == 0) {
            print ("available command:\n");// print all command per line
            for (int i = 0; i < _NUM_OF_CMD; i++) {
                print ("\t");
                print (keyworld[i]);
                print ("\n\r");
            }
        } else {
            print ("command: '");
            print ((char*)argv[i]);
            print ("' Not found.\n\r");
        }
        i++;
    }
    return 0;
}

#ifdef _USE_COMPLETE
//*****************************************************************************
// completion callback for microrl library
char ** complet (int argc, const char * const * argv)
{
    int j = 0;

    compl_world [0] = NULL;

    // if there is token in cmdline
    if (argc == 1) {
        // get last entered token
        char * bit = (char*)argv [argc-1];
        // iterate through our available token and match it
        for (int i = 0; i < _NUM_OF_CMD; i++) {
            // if token is matched (text is part of our token starting from 0 char)
            if (strstr(keyworld [i], bit) == keyworld [i]) {
                // add it to completion set
                compl_world [j++] = keyworld [i];
            }
        }
    }   else if ((argc > 1) && (strcmp (argv[0], _CMD_VER)==0)) { // if command needs subcommands
        // iterate through subcommand for command _CMD_VER array
        for (int i = 0; i < _NUM_OF_VER_SCMD; i++) {
            if (strstr (ver_keyworld [i], argv [argc-1]) == ver_keyworld [i]) {
                compl_world [j++] = ver_keyworld [i];
            }
        }
    } else { // if there is no token in cmdline, just print all available token
        for (; j < _NUM_OF_CMD; j++) {
            compl_world[j] = keyworld [j];
        }
    }

    // note! last ptr in array always must be NULL!!!
    compl_world [j] = NULL;
    // return set of variants
    return compl_world;
}
#endif

//*****************************************************************************
void sigint (void)
{
    print ("^C catched!\n\r");
}
#endif
