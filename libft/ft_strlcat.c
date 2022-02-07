/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:25:06 by scass             #+#    #+#             */
/*   Updated: 2021/04/09 06:56:24 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (dest[j] != '\0' && j < size)
		j++;
	i = j;
	while (src[j - i] && j + 1 < size)
	{
		dest[j] = src[j - i];
		j++;
	}
	if (i < size)
		dest[j] = '\0';
	return (i + ft_strlen(src));
}
