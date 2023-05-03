#include <stddef.h>
#include <stdint.h>
struct Char {
  uint8_t character;
  uint8_t color;
};
enum {
  PRINT_COLOR_BLACK = 0,
  PRINT_COLOR_BLUE = 1,
  PRINT_COLOR_GREEN = 2,
  PRINT_COLOR_CYAN = 3,
  PRINT_COLOR_RED = 4,
  PRINT_COLOR_MAGENTA = 5,
  PRINT_COLOR_BROWN = 6,
  PRINT_COLOR_LIGHT_GRAY = 7,
  PRINT_COLOR_DARK_GRAY = 8,
  PRINT_COLOR_LIGHT_BLUE = 9,
  PRINT_COLOR_LIGHT_GREEN = 10,
  PRINT_COLOR_LIGHT_CYAN = 11,
  PRINT_COLOR_LIGHT_RED = 12,
  PRINT_COLOR_PINK = 13,
  PRINT_COLOR_YELLOW = 14,
  PRINT_COLOR_WHITE = 15,
};
struct Char *buffer = (struct Char *)0xb8000;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

int kernel_main() {
  char buff[] = "hello world";
  for (size_t i = 0; i < 11; i++) {
    buffer[i] = (struct Char){
      character : (uint8_t)buff[i],
      color : color,
    };
  }
}