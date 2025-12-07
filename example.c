#define LIBENV_IMPLEMENTATION
#include "libenv.h"
#include <stdio.h>

int main(void) {
  if (libenv_load(".env.example") != 0) {
    printf("Failed to load .env\n");
    return 1;
  }

  char *hello = libenv_get("HELLO");
  printf("Hello: %s\n", hello);

  return 0;
}
