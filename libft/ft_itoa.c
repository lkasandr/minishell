/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:42:23 by scass             #+#    #+#             */
/*   Updated: 2021/04/09 07:52:02 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int		count;
	long	res;

	res = n;
	count = 1;
	if (res < 0)
	{
		count++;
		res *= (-1);
	}
	while (res >= 10)
	{
		count++;
		res /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	res;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * ft_size(n) + 1);
	if (!(str))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	res = n;
	if (res < 0)
		res *= (-1);
	str[ft_size(n) - i++] = '\0';
	while (res >= 10)
	{
		str[ft_size(n) - i++] = (res % 10) + '0';
		res /= 10;
	}
	str[ft_size(n) - i++] = (res % 10) + '0';
	return (str);
}
