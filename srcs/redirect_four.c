#include "minishell.h"

char	*cut_redirect(char *str, t_env *env, t_store *token, int i)
{
	char	*tmp;

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!check_str(str[i]))
		return (NULL);
	str = get_str_redir(str, &i, env);
	fill_struct_redirect(token, str, i);
	tmp = ft_substr(str, i, ft_strlen(str) - i);
	if (!tmp)
		ft_error(1);
	return (tmp);
}
