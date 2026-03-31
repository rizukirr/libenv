#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIBENV_IMPLEMENTATION
#include "../libenv.h"

static void write_file(const char *path, const char *contents) {
  FILE *f = fopen(path, "w");
  assert(f != NULL);
  fputs(contents, f);
  fclose(f);
}

int main(void) {
  const char *path1 = "tests/.env.one";
  const char *path2 = "tests/.env.two";

  write_file(path1,
             "HELLO=world\n"
             "SPACED =  value with spaces  \n"
             "# comment\n"
             "EMPTY=\n");

  assert(libenv_load((char *)path1) == 0);
  assert(strcmp(libenv_get("HELLO"), "world") == 0);
  assert(strcmp(libenv_get("SPACED"), "value with spaces") == 0);
  assert(strcmp(libenv_get("EMPTY"), "") == 0);
  assert(libenv_get("MISSING") == NULL);

  if (getenv("PATH") != NULL) {
    assert(libenv_get("PATH") == NULL);
  }

  write_file(path2,
             "HELLO=again\n"
             "NEW_KEY=fresh\n");

  assert(libenv_load((char *)path2) == 0);
  assert(strcmp(libenv_get("HELLO"), "again") == 0);
  assert(strcmp(libenv_get("NEW_KEY"), "fresh") == 0);
  assert(libenv_get("SPACED") == NULL);
  if (getenv("PATH") != NULL) {
    assert(libenv_get("PATH") == NULL);
  }

  remove(path1);
  remove(path2);
  return 0;
}
