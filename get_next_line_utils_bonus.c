#include "get_next_line.h"

char	*extract_line_eof(char **str)
{
	char	*line;

	line = NULL;
	if (!(*str) || !(**str))
	{
		free(*str);
		(*str) = NULL;
		return (NULL);
	}
	line = ft_strdup((*str));
	if (!line)
		return (NULL);
	free((*str));
	(*str) = NULL;
	return (line);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*sub;
	int		i;
	int		len_sub;

	i = start -1;
	len_sub = 0;
	while (++i < len)
		len_sub++;
	sub = NULL;
	sub = malloc(sizeof(char) * (len_sub + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (start < len && s[start])
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;
	size_t	i;

	i = -1;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = NULL;
	new = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new)
		return (NULL);
	len1 = -1;
	while (s1[++len1])
		new[++i] = s1[len1];
	len2 = -1;
	while (s2[++len2])
		new[++i] = s2[len2];
	new[++i] = '\0';
	return (new);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(s);
	dup = NULL;
	if (!s)
		return (dup);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (s[++i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}
