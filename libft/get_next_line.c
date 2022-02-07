/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:48:06 by scass             #+#    #+#             */
/*   Updated: 2021/04/12 12:23:28 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static size_t	ft_free(char **buf)
{
	if (*buf)
		free(*buf);
	*buf = NULL;
	return (-1);
}

static char	*search_n(char *s, int n)
{
	while (*s)
	{
		if (*s == n)
		{
			*s = '\0';
			return ((char *)s);
		}
		s++;
	}
	if (*s == n)
	{
		*s = '\0';
		return ((char *)s);
	}
	else
		return (0);
}

static void	new_remaind(char **remaind, char **line, char *ptr_n)
{
	char	*tmp;

	*line = ft_strdup(*remaind);
	if (!(*line))
		ft_free(remaind);
	tmp = *remaind;
	*remaind = ft_strdup(ptr_n + 1);
	if (!(*remaind))
		ft_free(remaind);
	ft_free(&tmp);
}

static char	*check_file(char **remaind, char **line)
{
	char			*ptr_n;

	ptr_n = NULL;
	if (*remaind)
	{
		ptr_n = search_n(*remaind, '\n');
		if ((ptr_n))
			new_remaind(remaind, line, ptr_n);
		else
		{
			*line = ft_strdup(*remaind);
			ft_free(remaind);
		}
	}
	else
		*line = ft_strdup("");
	return (ptr_n);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	size_t		byte;
	char		*ptr_n;
	static char	*remaind;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!(buf) || read(fd, buf, 0) < 0 || BUFFER_SIZE < 1 || !line || fd < 0)
		return (ft_free(&buf) * ft_free(&remaind) * -1);
	ptr_n = check_file(&remaind, line);
	byte = 1;
	while (!ptr_n && byte)
	{
		byte = read(fd, buf, BUFFER_SIZE);
		buf[byte] = '\0';
		ptr_n = search_n(buf, '\n');
		if ((ptr_n))
			remaind = ft_strdup(ptr_n + 1);
		*line = ft_strjoin(*line, buf);
	}
	free(buf);
	if (!byte && !ptr_n)
		return (ft_free(&remaind) * 0);
	else
		return (1);
}
