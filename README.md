# libenv

A single-header C library for loading `.env` files into a fast internal key/value store.

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

Loads key/value pairs from the specified file into libenv's internal store.

- Returns `0` on success
- Returns `-1` on failure (file not found)
- Replaces any previously loaded libenv data

### `char *libenv_get(char *key)`

Gets the value of a key from libenv's internal store.

- Returns pointer to the value string
- Returns `NULL` if the key is not loaded

## Notes

- `libenv` no longer calls `setenv()` or reads from `getenv()`
- Values loaded by `libenv_load()` are only visible through `libenv_get()`
- Lookups use an internal hash table optimized for repeated reads

## License

See [LICENSE](LICENSE) file for details.
