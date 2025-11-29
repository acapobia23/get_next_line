#include "get_next_line.h"
/*  TEST PER READ E BUFFER

int main(void)
{
    int fd;
    char *buffer;
    int n;

    fd = open("lorem.txt", O_RDONLY);
    n = 1;
    if (fd < 0)
    {
        perror("Error opening file\n");
        return 1;
    }
    while ((buffer = fd_reader(fd)) != NULL)
    {
        printf("linea %d: %s\n", n, buffer);
        n++;
        free(buffer);
    }
    close(fd);
    return 0;
}*/

/*  TEST PER SUBSTR

int main()
{
    char *s = "Hello, world!";
    unsigned int start = 7;
    size_t len = 5;
    char *substr = ft_substr(s, start, len);

    if (substr)
    {
        printf("Substring: %s\n", substr);
        free(substr);
    }
    else
    {
        printf("ft_substr failed to allocate memory\n");
    }

    return 0;
}*/

/*  TEST PER READ E ASSEMBLE

int main()
{
    int fd = open("test.txt", O_RDONLY); // replace "test.txt" with your test file
    char *buffer = NULL;
    char *line;

    if (fd < 0)
    {
        perror("Error opening file\n");
        return 1;
    }

    while ((line = read_and_assemble(&buffer, fd)) != NULL)
    {
        printf("Line: %s\n", line);
        free(line);
    }

    free(buffer);
    close(fd);
    return 0;
}*/

