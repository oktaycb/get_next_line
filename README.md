# Get Next Line (get_next_line)

This project is part of the 42 school curriculum. The goal is to write a function called `get_next_line` that can read from a file descriptor, one line at a time.

## 📝 Project Description

`get_next_line` reads the next line from a given file descriptor and returns it. Each time the function is called, it returns the next line until it reaches the end of the file. This project is a fundamental step in understanding static variables, memory management, and file I/O operations in C programming.

## ✨ Core Features

- **Use of Static Variables:** It uses a static variable (`stash`) to maintain data integrity between function calls.
- **Dynamic Memory Management:** It performs dynamic memory management with `malloc` and `free` to store lines and the intermediate buffer.
- **BUFFER_SIZE:** It works with a buffer size that can be set at compile time with the `-D BUFFER_SIZE=n` flag. This allows for optimizing reading performance.
- **Multiple File Descriptor Support:** It can read from multiple file descriptors at the same time (this is a bonus feature, and this version of the project does not support multiple files simultaneously as it uses a single static variable).

## 🛠️ How It Works

The function's logic follows these steps:

1.  **Read Data:** Data is read from the file descriptor up to `BUFFER_SIZE` using the `read` function.
2.  **Store Data (`stash`):** The read data is stored in a linked list (usually called `stash`) of type `t_list`. This static variable allows the function to remember its position for the next call.
3.  **Search for Newline:** The stored data is searched for a newline character (`\n`).
4.  **Extract Line:** When a newline character is found, the portion from the beginning to this character is extracted as a new string, which becomes the function's return value.
5.  **Update `stash`:** The remaining data (the part after the newline character) is kept in the `stash` for the next `get_next_line` call.
6.  **End of File (EOF) and Error Handling:** When the `read` function returns `0`, it means the end of the file has been reached. In case of an error (`-1`) or at the end of the file, `NULL` is returned.

## 🚀 Usage

### Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters

- `int fd`: The file descriptor of the file to be read.

### Return Value

- **The read line:** If successful, a string containing the line that was read.
- **`NULL`:** If the end of the file has been reached or an error has occurred.

### Compilation

You can create a `main.c` file like the one below to test your project:

```c
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    // Create a file named "test.txt" and write a few lines in it.
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    // Read line by line until the end of the file and print to the screen
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line); // Free the memory allocated by get_next_line
    }

    close(fd);
    return (0);
}
```

You can use the following command to compile your project:

```bash
# To use the default BUFFER_SIZE:
gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl_tester

# To specify a custom BUFFER_SIZE:
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_tester
```

### Execution

```bash
./gnl_tester
```




  
