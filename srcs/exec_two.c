#include "minishell.h"

void	ft_clearing(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free (str[i]);
		i++;
	}
	if (str)
	{
		free (str);
		str = NULL;
	}
}
