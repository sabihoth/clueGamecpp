#ifndef COLOR_H
#define COLOR_H

#include <string.h>
#include <iostream>

//Definitions of colors used when printing to the terminal

#define COLOR(code) "\e[1;" + code + "m"
#define BLUE ("\e[1;34m")
#define MAGENTA ("\e[1;35m")
#define YELLOW ("\e[1;33m")
#define WHITE ("\e[1;30m")

#endif
