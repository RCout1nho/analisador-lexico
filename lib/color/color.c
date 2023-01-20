#include <stdio.h>
#include "color.h"

void set_color_red() { printf("\033[1;31m"); }

void set_color_green() { printf("\033[0;32m"); }

void set_color_white() { printf("\033[1;37m"); }


void set_color_blue() { printf("\033[1;34m"); }

void set_bg_color_black() { printf("\033[40m"); }

void set_color_reset() { printf("\033[0m"); }