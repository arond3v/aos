#include "print.h"
struct Char *buffer = (struct Char *)0xb8000;

void clrscr() {
  for (size_t height = 0; height < HEIGHT; height++) {
    for (size_t width = 0; width < WIDTH; width++) {
      buffer[height * WIDTH + width] = (struct Char){
        character : ' ',
        color : PRINT_COLOR_BLACK | (PRINT_COLOR_BLACK << 4),
      };
    }
  }
}