/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 02:15:54 by scass             #+#    #+#             */
/*   Updated: 2021/04/09 06:57:12 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	cc;
	int		i;

	i = ft_strlen(s);
	str = (char *)s;
	cc = (char)c;
	while (i >= 0)
	{
		if (str[i] == cc)
			return (&str[i]);
		i--;
	}
	if (cc == '\0')
		return (str);
	return (NULL);
}
