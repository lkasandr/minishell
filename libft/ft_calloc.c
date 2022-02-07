/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 01:48:52 by scass             #+#    #+#             */
/*   Updated: 2021/04/07 09:08:33 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*str;

	str = (void *)malloc(n * size);
	if (!str)
		return (NULL);
	ft_bzero(str, n * size);
	return ((void *)str);
}
