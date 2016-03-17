#ifndef kbhit_h
#define kbhit_h

#include <stdlib.h> 
#include <unistd.h> 
#include <sys/select.h> 
#include <termios.h> 
#include <time.h> 
#include <stdio.h>

class Kbhit{
	public:
	static struct termios old_termios, new_termios;
	static void resetTermios();
	static void initTermios();
	static int kbhit();
	static char getch();

};

#endif
