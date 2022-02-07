/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:37:28 by scass             #+#    #+#             */
/*   Updated: 2021/04/21 04:07:34 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *str, char c)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	**ft_free(char **s)
{
	int				i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	*ft_put(char const *str, size_t n)
{
	char			*new;
	size_t			i;

	i = 0;
	new = (char *)malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	while (str[i] && i < n)
	{
		new[i] = str[i];
		i++;
	}
	while (i < n)
	{
		new[i] = '\0';
		i++;
	}
	new[n] = '\0';
	return (new);
}

char	**ft_split(char const *str, char c)
{
	int				i;
	int				j;
	int				k;
	char			**s;

	i = 0;
	k = 0;
	s = (char **)malloc(sizeof(char *) * (ft_count(str, c) + 1));
	if (!s)
		return (NULL);
	while (str[i])
	{
		while (str[i] == c)
			i++;
		j = i;
		while (str[i] && str[i] != c)
			i++;
		if (i > j)
			s[k++] = ft_put(str + j, i - j);
		if (!s)
			return (ft_free(s));
	}
	s[k] = NULL;
	return (s);
}
