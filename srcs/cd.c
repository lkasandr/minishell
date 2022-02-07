#include "minishell.h"

static void	change_env(t_env *env, char *path, char *oldpwd)
{
	t_env	*p;

	p = env;
	while (p)
	{
		if (ft_strcmp(p->key, "OLDPWD") == 0)
		{
			free(p->value);
			p->value = ft_strdup(oldpwd);
		}
		if (ft_strcmp(p->key, "PWD") == 0)
		{
			free(p->value);
			p->value = ft_strdup(path);
		}
		p = p->next;
	}
}

char	*get_oldpwd(t_env *env)
{
	char	*oldpwd;
	t_env	*p;

	p = env;
	while (p)
	{
		if (ft_strcmp(p->key, "PWD") == 0)
			oldpwd = ft_strdup(p->value);
		p = p->next;
	}
	return (oldpwd);
}

static int	check_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	if (count == 1 && ft_strlen(argv[0]) > 2)
		return (0);
	return (1);
}

static void	get_argv(char *str, char *r_path)
{
	if (ft_strncmp(str, "~", 1) == 0)
	{
		r_path = ft_strdup(getenv("HOME"));
		r_path = ft_strjoin(r_path, str);
		str = r_path;
	}
	if (chdir(str) < 0)
		print_error(strerror(errno));
}

int	our_cd(int argc, char **argv, t_env *env, t_env *export)
{
	char	*r_path;
	char	dir[4096];
	char	*oldpwd;

	r_path = NULL;
	oldpwd = get_oldpwd(env);
	if (!check_argv(argv))
	{
		print_error(argv[0]);
		return (0);
	}
	if (argc == 1)
	{
		argv[0] = getenv("HOME");
		if (chdir(argv[0]) < 0)
			print_error(strerror(errno));
	}
	if (argc >= 2)
		get_argv(argv[1], r_path);
	argv[1] = getcwd(dir, 4096);
	change_env(env, argv[1], oldpwd);
	change_env(export, argv[1], oldpwd);
	return (0);
}
