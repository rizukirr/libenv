#ifndef LIBENV_H
#define LIBENV_H

int libenv_load(char *env_file);
char *libenv_get(char *key);

#ifdef LIBENV_IMPLEMENTATION

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *trim(char *str) {
  while (isspace((unsigned char)*str))
    str++;

  if (*str == 0)
    return str;

  char *end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  end[1] = '\0';

  return str;
}

int libenv_load(char *env_file) {
  FILE *f = fopen(env_file, "r");
  if (!f)
    return -1;

  char line[512];

  while (fgets(line, sizeof(line), f)) {
    char *s = trim(line);

    // ignore comments & empty lines
    if (*s == '#' || *s == '\0')
      continue;

    // find '='
    char *eq = strchr(s, '=');
    if (!eq)
      continue;

    *eq = '\0';
    char *key = trim(s);
    char *value = trim(eq + 1);

    // set environment variable (overwrite=true)
    setenv(key, value, 1);
  }

  fclose(f);
  return 0;
}

char *libenv_get(char *key) { return getenv(key); }

#endif // LIBENV_IMPLEMENTATION

#endif // LIBENV_H
