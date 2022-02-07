/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scass <scass@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 04:57:23 by scass             #+#    #+#             */
/*   Updated: 2021/04/09 10:17:37 by scass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elem;

	if (!lst || !new)
		return (1);
	elem = *lst;
	if (elem)
	{
		while (elem->next)
			elem = elem->next;
		elem->next = new;
		new->next = NULL;
		return (0);
	}
	else
		*lst = new;
	return (0);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->content = content;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*elem;

	len = 0;
	if (lst == NULL)
		return (0);
	if (lst)
	{
		elem = lst;
		while (elem)
		{
			elem = elem->next;
			len++;
		}
	}
	return (len);
}
