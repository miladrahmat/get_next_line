# get_next_line
**The goal of this project is to add a convenient function to your collection and learn about static variables**

## Content

- [Introduction](#introduction)
- [Helper functions](#helper-functions)
- [Bonus](#bonus)
- [Testing](#testing)

## Introduction

The `get_next_line()` function takes a file descriptor as a parameter, reads a line from it and returns the line which was read (including the *newline charachter* `\n`.

If you call the function again with the same file descriptor, the function will return the next line from it. If there are no more lines to read or an error occured the function will return `NULL`.

## Helper functions

The subject wouldn't let me use [libft](https://github.com/miladrahmat/Libft), so I had to copy a few functions from it and write a few new ones to the [utilities file](https://github.com/miladrahmat/get_next_line/blob/main/get_next_line_utils.c). Here's a list of the helper funtctions used in this project:

| Function name | Description                                                                                   |
|---------------|-----------------------------------------------------------------------------------------------|
| `ft_strjoin`  | allocates and returns a new string, which is the result of the concatenation of `s1` and `s2` |
| `ft_substr`   | allocates and returns a substring from the string `s`                                         |
| `ft_strlen`   | computes the length of the given string                                                       |
| `ft_strlen_nl`| computes the length of the given string until newline                                         |
| `ft_strchr`   | locates the first occurance of `c` in the string `s`                                          |

## Bonus

This project is very straghtforward and doesn't allow complex bonuses. However there is a bonus part with the following requirements:
- Develop the `get_next_line()` function using only one static variable.
- The `get_next_line()` can manage multiple file descriptors at the same time.

## Testing

You can test this function by cloning the repository:
```
git clone https://github.com/miladrahmat/get_next_line.git
```
You will have to create a test file with some text on it and write a main function that should open the file with a file descriptor that you can send to the `get_next_line()` function. 

For example:
```
#include <stdio.h>
#include <fcntl.h>
int	main()
{
	int		fd;
	int		lines;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	lines = 0;
	while (lines < 1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		lines++;
	}
	return (0);
} 
```
Or for the bonus you can test with multiple file descriptors:
```
#include <stdio.h>
#include <fcntl.h>
int	main()
{
	int		fd;
	int		fd1;
	int		fd2;
	int		lines;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	lines = 0;
	while (lines < 7)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		line = get_next_line(fd1);
		printf("%s", line);
		free(line);
		line = get_next_line(fd2);
		printf("%s", line);
		free(line);
		lines++;
	}
	return (0);
} 
```
Because the `get_next_line()` will have to read files, you will have to add the following option to your function call in addition to your usual flags:
```
-D BUFFER_SIZE=42
```
This will define the buffer size to `42`. You can change this value to be whatever you want. 
