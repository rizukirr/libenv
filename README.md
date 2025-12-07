# libenv

A simple single-header C library for loading environment variables from .env files.

## Usage

Include the header file in one source file with the implementation macro defined:

```c
#define LIBENV_IMPLEMENTATION
#include "libenv.h"
```

In other files, just include the header:

```c
#include "libenv.h"
```

### Example

```c
#define LIBENV_IMPLEMENTATION
#include "libenv.h"
#include <stdio.h>

int main(void) {
  if (libenv_load(".env") != 0) {
    printf("Failed to load .env\n");
    return 1;
  }

  char *value = libenv_get("MY_VAR");
  printf("MY_VAR: %s\n", value);

  return 0;
}
```

### .env File Format

```
# This is a comment
MY_VAR=my_value
ANOTHER_VAR=another_value
```

## API

### `int libenv_load(char *env_file)`

Loads environment variables from the specified file.

- Returns `0` on success
- Returns `-1` on failure (file not found)

### `char *libenv_get(char *key)`

Gets the value of an environment variable.

- Returns pointer to the value string
- Returns `NULL` if the variable is not set

## License

See LICENSE file for details.
