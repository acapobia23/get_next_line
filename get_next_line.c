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
	static char	*str = NULL;
	int			end_file;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (check_str(str) == 0)
		return (extract_line(&str));
	end_file = new_call(&str, fd);
	if (end_file == 0)
		return (extract_line_eof(&str));
	else if (end_file == -1)
	{
		if (str)
			free(str);
		return (NULL);
	}
	return (get_next_line(fd));
}

// #include <stdio.h>
// int main()
// {
//     int fd = open("test.txt", O_RDONLY);
//     char *line;
//     int i = 1;

//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return 1;
//     }

//     while ((line = get_next_line(fd)) != NULL)
//     {
// 		if (i == 5)
// 		{
// 			close(fd);
// 			if (line)
// 				free(line);
// 			break ;\
// 		}
//         printf("Linea %d: %s",i ,line);
//         i++;
// 		if (line)
//         	free(line);
//     }
// 	printf("\n\n2 while\n\n");
//     int fd2 = open("test.txt", O_RDONLY);
//     while ((line = get_next_line(fd2)) != NULL)
//     {
//         printf("Linea %d: %s",i ,line);
//         i++;
//         free(line);
//     }
//     close(fd);
//     return 0;
// }