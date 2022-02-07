#include "minishell.h"

void	print_declare_export(t_env *export)
{
	t_env	*tmp;

	sort_struct(export);
	tmp = export;
	while (tmp != NULL)
	{
		printf("declare -x %s", tmp->key);
		if (!strcmp(tmp->value, "\0"))
			printf("\n");
		else
			printf("=\"%s\"\n", tmp->value);
		tmp = tmp->next;
	}
}
