#include "print.h"
struct Char *buffer = (struct Char *)0xb8000;
int buff_h = 0, buff_v = 0;

void clrscr() {
  for (size_t height = 0; height < HEIGHT; height++) {
    for (size_t width = 0; width < WIDTH; width++) {
      buffer[height * WIDTH + width] = (struct Char){
        character : ' ',
        color : (PRINT_COLOR_BLACK << 4) | PRINT_COLOR_BLACK,
      };
    }
  }
}
void printstr(char *buff, uint8_t color) {
  int i = 0;
  while (buff[i] != '\0') {
    if (buff[i] == '\n') {
      buff_h = 0;
      buff_v++;
    } else {
      buffer[buff_v * WIDTH + buff_h] = (struct Char){
        character : buff[i],
        color : color,
      };
      if (buff_h + 1 == WIDTH) {
        buff_v++;
        buff_h = 0;
      } else
        buff_h++;
    }
    i++;
  }
}