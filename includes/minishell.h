/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:25:16 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/13 00:19:13 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**
 * 	A wise person once said, that knowledge came from books
 * RTFM
 */
# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <stddef.h>
# include <limits.h>
# include <fcntl.h>
// # include <valgrind/memcheck.h>

/**
 * Setting your vocabulary makes you wiser
 */
# define NOTHING	0
# define R_REDIR	1
# define L_REDIR	2
# define DR_REDIR	3
# define DL_REDIR	4

/**
 * Defining your tools and refining them is the key
 */
extern int	g_exit;

typedef struct s_redir
{
	char		**file;
	size_t		*flag;
	size_t		flag_len;
}	t_redir;

typedef struct s_cmd
{
	char			**argument;
	char			*command;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_sh
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp_str;
	size_t			input_len;
	ssize_t			expand_len;
	ssize_t			dolla_size;
	size_t			euro;
	size_t			sq;
	size_t			dq;
	size_t			sr;
	size_t			p;
}	t_sh;

typedef struct s_exec
{
	int		**fd;
	ssize_t	*id;
	size_t	flag;
	size_t	len;
	size_t	i;
	char	*path;
	char	**env_kid;
}	t_exec;

typedef enum e_boolean
{
	false,
	true
}	t_bool;

typedef struct s_lex
{
	t_env	*env;
	t_sh	*sh;
	t_cmd	*cmd;
}	t_lex;

/**
 * Teaching kinds how to manipulate tools
 */
ssize_t	get_expand_len(char *name, t_env *env);
char	*get_env_value(t_env *env, char *name);
char	*ft_append_char(char *name, char c);
void	ft_fill_expand(char *str, t_lex *lex);
void	ft_print_char_arr(char **array);
char	*ft_expand(t_env *lst, char *str);
void	new_prompt(int val);
void	ft_strjustcat(char *dst, const char *src);
int		minishell(char **env);
int		ft_init(t_cmd **cmd, t_env **env);
int		ft_parse(char *str, t_lex *lex);
void	ft_fill_arg(t_lex *lex);
int		check_redirections(char *str, t_lex *lex);
int		check_quotes(char *str, char quote, t_lex *lex);
int		parser_stage1(char *str, t_lex *lex);
int		parser_stage2(char *str, t_lex *lex);
int		ft_check_expand(char *str, t_lex *lex);
int		check_p(char *str, t_lex *lex);
void	check_fill_redirections(char *str, t_lex *lex);
void	check_fill_quotes(char *str, char c, t_lex *lex);
void	ft_fill_redir(t_lex *lex);
t_env	*push_lst(t_env *new, t_env *lst, char *env_name, char *env_value);
t_env	*push_env(t_env *env_list, char *env_name, char *env_value);
t_env	*ft_env(char **env);
void	ft_fill_command(char **tab, size_t i, t_lex *lex);
void	ft_fill_arg(t_lex *lex);
void	ft_append_back(char **str, char c);

/**
 * Initialization of program
 */
void	shell_prompt(char **env);
void	exec_cmd(t_env *lst, t_cmd *cmd_lst);
t_cmd	*ft_cmd_lst(char *str);
// t_cmd	*ft_lst_init(char *str);

void	ft_expander(t_env *lst, char *str);

/**
 * Buitlins
 */
t_env	*ft_env(char **env);
t_env	*push_env(t_env *lst, char *env_name, char *env_value);
t_env	*push_lst(t_env *new, t_env *lst, char *env_name, char *env_value);

void	ft_echo(t_cmd *cmd_lst);
void	div_env(char *str, t_env *lst);
t_env	*check_exist(t_env *lst, char *str);
t_env	*check_stack(t_env *new_node, t_env *lst);
void	join_str(t_cmd *cmd_lst, char **len, int i, t_env **check);
void	get_sub(char **store, char *str, char **env_name, char **env_value);

void	ft_pwd(t_env *lst);
void	ft_unset(t_env *lst, t_cmd *cmd_lst);
void	ft_cd(t_cmd *cmd_lst, t_env *lst);
void	ft_export(t_env *lst, t_cmd *cmd_lst);
void	lonely_export(t_env *lst);
void	div_env(char *str, t_env *lst);
void	ft_exit(t_cmd *cmd_lst);

/**
 * UTILS
 */
void	print_list_env(t_env *head, t_cmd *cmd_lst);
void	print_lst(t_env *lst);

char	*get_pwd(void);
t_env	*search_pwd(t_env *lst);

int		get_args_len(t_cmd *cmd_lst);
int		get_len(char *str);
int		get_lst_len(t_env *lst);
int		iter_diff(t_env *lst, t_env *new_node);
size_t	get_cmd_len(t_cmd *cmd);

char	*check_validity(t_cmd *cmd_lst);
size_t	check_type(t_cmd *cmd_lst, t_exec **exec);

/**
 * EXECUTING FUNCTIONS
 */
void	exec_sys(t_env *lst, t_cmd *cmd_lst);
void	main_child(t_env *lst, t_cmd *cmd_lst, char *path);
char	**get_path(t_env *lst);
char	*check_access(t_env *lst, t_cmd *cmd_lst);
char	**lst_to_char(t_env **lst);

void	redirect(t_env *lst, t_cmd *cmd_lst, int flag, int status);
void	exec(t_env *lst, t_cmd *cmd_lst, int status, char *file);

void	exec_pipe(t_env *lst, t_cmd *cmd_lst);
size_t	exec_builtin(t_env *lst, t_cmd *cmd_lst);
void	exec_alone(t_cmd *cmd_lst, t_env *lst, t_exec *exec);
void	exec_sys(t_env *lst, t_cmd *cmd_lst);
void	pipe_exec(t_env *lst, t_cmd *cmd_lst, t_exec *exec);
void	fork_arr(t_env *lst, t_cmd *cmd_lst, t_exec *exec);
void	loop_lst(t_env *lst, t_cmd **cmd_lst, t_exec *exec);
void	pipe_arr(t_exec *exec);
void	close_pipes(t_exec *exec);
size_t	check_builtin(t_cmd *cmd_lst);
void	check_path(t_cmd *cmd_lst, t_exec **exec);
size_t	check_all_path(t_env *lst, t_cmd *cmd_lst);
size_t	main_child2(t_cmd *cmd_lst, t_exec *exec);
void	check_pos(t_env *lst, t_cmd *cmd_lst, t_exec *exec);
size_t	exec_child(t_cmd *cmd_lst, t_exec *exec);

void	redirect_in(t_env *lst, t_cmd *cmd_lst);
void	redirect_out(t_env *lst, t_cmd *cmd_lst);
void	append_out(t_env *lst, t_cmd *cmd_lst);
void	here_doc(t_env *lst, t_cmd *cmd_lst);

/**
 * FREE FUNCTONS
 */
void	lst_free(t_cmd *cmd_lst, t_env *lst);
void	free_cmd(t_cmd **cmd_lst);
void	free_env_lst(t_env *lst);
void	free_split(char **split_res);
void	free_env_kid(char **env_kid);
void	free_exec(t_exec **exec);
void	free_cmd_lst(t_cmd *cmd_lst);
void	free_child(t_exec *exec, t_env *lst, t_cmd *cmd_lst);
void	free_split_baqala(char **split_res, int i);

void	sig_handler(int val);
void	err_msg(t_cmd *cmd_lst, char *val, char *err);

/**
 * ERROR FUNCTONS
 */
void	export_error(char *val);

int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_atol(const char *str);
char	*ft_ltoa(size_t n);

void	ft_env_init(t_env *lst);
void	ft_cmd_init(t_cmd *cmd_lst);
void	ft_exec_init(t_exec *exec);

#endif
