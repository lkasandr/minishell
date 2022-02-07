/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:36:21 by scass             #+#    #+#             */
/*   Updated: 2021/04/09 06:52:04 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	cc;

	cc = (unsigned char)c;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (len--)
	{
		*d++ = *s++;
		if (*(d - 1) == cc)
			return (d);
	}
	return (NULL);
}
