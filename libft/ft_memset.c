/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:43:25 by scass             #+#    #+#             */
/*   Updated: 2021/04/09 06:53:00 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	*d;
	unsigned char	cc;

	d = (unsigned char *)dest;
	cc = (unsigned char)c;
	while (len--)
		*d++ = cc;
	return (dest);
}
