/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 22:41:18 by scass             #+#    #+#             */
/*   Updated: 2021/04/09 06:48:15 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len(long long int n)
{
	int			len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

size_t	ft_size_t_len(size_t nbr)
{
	size_t		len;

	len = 0;
	while (nbr / 10 >= 1)
	{
		nbr /= 10;
		len += 1;
	}
	len++;
	return (len);
}
