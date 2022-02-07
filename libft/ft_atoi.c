/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 07:45:28 by scass             #+#    #+#             */
/*   Updated: 2021/04/21 06:47:58 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calc_res(const char *str, int i, unsigned long res, int r)
{
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if ((long)(r * res) > 2147483647)
			return (-1);
		if ((long)(r * res) < -2147483648)
			return (0);
		i++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				r;
	unsigned long	res;

	i = 0;
	r = 1;
	res = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			r = -1;
		i++;
	}
	if (ft_isdigit(str[i]))
		res = calc_res(str, i, res, r);
	else
		return (-1);
	return ((int)(r * res));
}
