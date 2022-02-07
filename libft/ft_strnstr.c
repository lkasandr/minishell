/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 15:41:16 by scass             #+#    #+#             */
/*   Updated: 2021/04/14 12:49:08 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *s1, char *s2, size_t len)
{
	size_t		j;
	size_t		i;

	i = 0;
	if (!(*s2))
		return (s1);
	while (s1[i] != '\0' && i < len)
	{
		j = 0;
		while (s2[j] == s1[i + j] && (i + j) < len)
		{
			if (s2[j + 1] == '\0')
				return (s1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
