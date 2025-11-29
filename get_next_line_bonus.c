#include "get_next_line.h"

void	add_buffer(char **buf, char **str)
{
	char	*tmp;

	tmp = NULL;
	if (!(*str))
		(*str) = ft_strdup((*buf));
	else
	{
		tmp = ft_strjoin((char const *)(*str), (char const *)(*buf));
		free((*str));
		(*str) = NULL;
		if (!tmp)
			return ;
		(*str) = tmp;
	}
	free((*buf));
}

int	new_call(char **str, int fd)
{
	char	*buf;
	int		byte_read;

	buf = NULL;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	byte_read = read(fd, buf, BUFFER_SIZE);
	buf[byte_read] = '\0';
	if (byte_read < 0)
	{
		free(buf);
		return (-1);
	}
	else if (byte_read == 0)
	{
		free(buf);
		return (0);
	}
	add_buffer(&buf, &(*str));
	if (!(*str))
		return (-1);
	return (byte_read);
}

char	*extract_line(char **str)
{
	char	*tmp;
	char	*line;
	int		i;
	int		j;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if (!(*str)[i])
	{
		line = ft_substr((*str), 0, i);
		free((*str));
		(*str) = NULL;
	}
	line = ft_substr((*str), 0, i + 1);
	j = i;
	while ((*str)[j])
		j++;
	tmp = ft_substr((*str), i + 1, j);
	free((*str));
	(*str) = tmp;
	return (line);
}

int	check_str(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (-1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	int			end_file;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (check_str(str[fd]) == 0)
		return (extract_line(&str[fd]));
	end_file = new_call(&str[fd], fd);
	if (end_file == 0)
		return (extract_line_eof(&str[fd]));
	else if (end_file == -1)
	{
		if (str[fd])
			free(str[fd]);
		return (NULL);
	}
	return (get_next_line(fd));
}

#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <file1> <file2> ...\n", argv[0]);
        printf("Or run with no arguments to read from stdin.\n\n");
        printf("⌨️ Reading from standard input (CTRL+D to stop):\n\n");

        char *line;
        int i = 1;

        while ((line = get_next_line(0)) != NULL)
        {
            printf("STDIN Line %d: %s", i++, line);
            free(line);
        }
        return 0;
    }

    int count = argc - 1;
    int fds[count];
    char *line;
    int done = 0;

    /* Open all files */
    for (int i = 0; i < count; i++)
    {
        fds[i] = open(argv[i + 1], O_RDONLY);
        if (fds[i] < 0)
        {
            perror(argv[i + 1]);
            fds[i] = -1;
        }
        else
        {
            printf("📄 Opened: %s (fd %d)\n", argv[i + 1], fds[i]);
        }
    }
    printf("\n--- READING INTERLEAVED LINES ---\n\n");

    int line_num = 1;

    while (!done)
    {
        done = 1;
        for (int i = 0; i < count; i++)
        {
            if (fds[i] < 0)
                continue;

            line = get_next_line(fds[i]);

            if (line)
            {
                printf("[%s] Line %d: %s", argv[i + 1], line_num, line);
                free(line);
                done = 0;
            }
        }
        line_num++;
    }

    for (int i = 0; i < count; i++)
        if (fds[i] > 2)
            close(fds[i]);

    return 0;
}
