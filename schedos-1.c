#include "schedos-app.h"
#include "x86sync.h"

/*****************************************************************************
 * schedos-1
 *
 *   This tiny application prints red "1"s to the console.
 *   It yields the CPU to the kernel after each "1" using the sys_yield()
 *   system call.  This lets the kernel (schedos-kern.c) pick another
 *   application to run, if it wants.
 *
 *   The other schedos-* processes simply #include this file after defining
 *   PRINTCHAR appropriately.
 *
 *****************************************************************************/

#ifndef PRINTCHAR
#define PRINTCHAR	('1' | 0x0C00)
#endif

#ifndef PRIORITY
#define PRIORITY 1
#endif

#ifndef SHARE
#define SHARE 10
#endif

#define SYSPRINT

void
start(void)
{
	int i;
	//set the priority
	sys_set_priority(PRIORITY);
	//set the share
	sys_set_share(SHARE);
	
	sys_yield();

	for (i = 0; i < RUNCOUNT; i++) {
		// Write characters to the console, yielding after each one.
	  
          #ifndef SYSPRINT
	  *cursorpos++ = PRINTCHAR;
	  #endif

	  #ifdef SYSPRINT
	  //system call that prints atomically
	  sys_print(PRINTCHAR);
	  #endif
	  
		sys_yield();
	}

	sys_exit(0);
}
