/* Apparently, ISO C does not permit variable arguments in macros so we have to define a function to kind of wrap in a macro. */

#ifndef __DEBUGMACRO_h__
#define __DEBUGMACRO_h__

#include <fstream>
#include <errno.h>
#include <stdarg.h>

#ifndef NDEBUG

#define BIT0 0x1
#define BIT1 0x2
#define BIT2 0x4
#define BIT3 0x8
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define debug_print(bit, os) \
    if(GLOBAL_DEBUG_BITS&bit) {\
    ERR_FS << os;}
#define debug_println(bit, os) \
    if(GLOBAL_DEBUG_BITS&bit) {\
    ERR_FS << os << std::endl;}
#else
#define debug_print(bit,os)
#endif


/* declaration of a global variable seen in other files - it has to be defined in one of the .c files (here: module.c)*/ 
extern unsigned int GLOBAL_DEBUG_BITS;	/* this variable will control the DEBUGGING bits relevant to debug and check_debug macros above.*/

/* Declare extern file stream to file which debug output will be sent to */
extern std::ofstream ERR_FS;

/* It returns "None" if errno (code error) is 0, and the error message corresponding to the code otherwise. */
#define clean_errno() (errno == 0 ? "None" : strerror(errno))


/* It just prints to the screen [ERROR] (file: line: error message) and additional string provided by the user. */
/* __FILE__ stores information about the current file and __LINE__ about the current line. */
/* This is a programmer who decides when to print this error statement. */


#endif
