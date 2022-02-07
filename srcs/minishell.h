#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <term.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <errno.h>
# include <sys/wait.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_store
{
	char			*word;
	struct s_store	*next;
}					t_store;

typedef struct s_minishell
{
	int	fork_status;
	int	exit_code;
	int	pipe_flag;
	int	fd_in_old;
	int	fd_out_old;
}				t_shell;

t_shell	g_sh;

void	our_sig_proc(int sig);
int		our_unset(t_env *env, t_env *export, char **argv, int count);
int		exec_bin(char **argv, t_env *env_value, char **env);
int		our_echo(char **argv);
int		our_pwd(char **argv);
int		our_env(t_env *env, char **argv, int count);
int		our_cd(int argc, char **argv, t_env *env, t_env *export);
int		our_export(int count, t_env *env, t_env *export, char **argv);
void	print_error(char *str);
char	*process_redirect(char *str, t_env *env, t_store *store);
int		our_redirect(char *word, t_env *env, t_store *token);
void	rl_replace_line(char *str, int i);
char	*get_key(char *token);
char	*get_value(char *token);
t_env	*add_node_env(t_env *env, char *key, char *value);
char	*process_dollar(char *str, int *i, t_env *env);
int		check_export_argument(char *arg);
void	ft_error(int code);
t_store	*add_node_token(t_store *token, char *str, int i);
int		execute_command(t_env *env, t_env *export,
			t_store *token, char **envp);
char	*process_value(char *val, t_env *env);
char	*process_pipe(char *str, t_env *env, t_store *token);
char	**split_token_word(char *word);
int		pipe_proc(t_env *env, char **envp, t_env *export, t_store *token);
int		command_handler(t_env *env, t_env *export, t_store *token, char **envp);
int		count_argument(char **argv);
int		check_redirect(t_store *token, t_env *env);
void	init_struct_env(t_env *env);
void	init_mini(void);
void	fill_struct_env(char **envp, t_env *env);
void	free_struct_store(t_store *token);
void	init_struct_store(t_store *token);
int		parser(char *str, t_env *env, t_store **token, t_env *export);
int		free_exit(t_store *store, t_env *env, t_env *export, int code);
char	*single_quotes(char *str, int *i, t_env *env, int flag);
char	*double_quotes(char *str, int *i, t_env *env);
char	*find_path(t_env *env, char *bin);
t_store	*get_pipe_struct(t_store *token);
char	**get_pipe_array(t_store *token);
int		check_redirect_in_pipe(char *word);
int		token_size(t_store *token);
void	redir_in_pipe(t_env *env, t_env *export, char **envp, t_store *tmp);
void	change_fd_pipe(int i, int fd[2], int fd2[2], int len);
void	close_fd(int fd[2], int fd2[2], int i);
void	waiting_pids(int i);
void	pid_err(char *str);
void	check_and_handler(t_env *env, t_env *export, t_store *tmp, char **envp);
int		get_k(char *arg);
int		check_export_argument(char *arg);
int		check_repeat(char *key, char *value, t_env *env);
char	*process_value(char *val, t_env *env);
void	add_env_export(char *key, char *value, t_env *env, t_env *export);
int		process_export(int count, char **argv, t_env *env, t_env *export);
void	fill_export(char *str, t_env *env, t_env *export);
int		export_error(char *str);
char	*get_value(char *token);
char	*get_key(char *token);
char	*handler_quot(char *str, int i, t_env *env);
void	print_declare_export(t_env *export);
void	sort_struct(t_env *export);
char	*check_right_redir(char *str, int i, t_env *env, t_store *token);
char	*check_left_redir(char *str, int i, t_env *env, t_store *token);
char	*process_str_redirect(char *str, t_env *env);
int		right_redirect(char *word);
char	*cut_redirect(char *str, t_env *env, t_store *token, int i);
char	*cut_double_redirect(char *str, t_env *env, t_store *token, int i);
char	*double_quotes_two(char *str, int *i, t_env *env);
int		check_str(char i);
char	*get_str_redir(char *str, int *i, t_env *env);
void	fill_struct_redirect(t_store *token, char *str, int i);
void	check_exit(char *str, t_store *token, t_env *env, t_env *export);
void	parse_redir_pipe(char *str, t_env *env, t_store **token, int flag);
char	*copy_str_without_quotes(char *str, int j, int i);
int		ft_free(char *str);
void	ft_clearing(char **str);
#endif