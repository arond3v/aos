#include "print.h"

int kernel_main() {
  clrscr();
  printstr("hello word\n", PRINT_COLOR_BLACK << 4 | PRINT_COLOR_CYAN);
}