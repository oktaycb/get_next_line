# Get_Next_Line
## Basic Informations

#### Function Prototype

```c
 char	*get_next_line(int fd);
```
#### Return value


| Value |  Description                       |
| :-------- |  :-------------------------------- |
| `Read line`      | correct behavior  |
| `NULL`      | nothing else to read or an error has occured|



| Function | Description                |
| :-------- | :------------------------- |
| `read()` | A line has been read |
| `malloc()` | EOF has been reached |
| `free()` | An error happene |



  
