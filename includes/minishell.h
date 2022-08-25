/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:25:16 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/25 15:23:00 by asanthos         ###   ########.fr       */
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
# include <limits.h>
# include <fcntl.h>
// # include <valgrind/memcheck.h>

/**
 * Setting your vocabulary makes you wiser
 */
# define NOTHING	-1
# define R_REDIR	0
# define L_REDIR	1
# define DR_REDIR	2
# define DL_REDIR	3
# define PIPE		4
# define S_QUOTE	5
# define D_QUOTE	6
# define CASHMONEY	7

/**
 * Defining your tools and refining them is the key
 */

typedef struct s_cmd
{
	char			*command;
	char			**argument;
	char			*o_token;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			**env_str;
	char			*name;
	char			*value;
	int				export_flag;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_exec
{
	int		**fd;
	int		*id;
	char	*path;
	char	**env_kid;
	int		flag;
	int		i;
}	t_exec;

/**
 * Teaching kinds how to manipulate tools
 */

/**
 * Initialization of program
 */
void	shell_prompt(char **env);
int		minishell(int ac, char **av, char **env);
void	ft_parse(t_env *lst, t_cmd *cmd_lst);
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
void	print_list_env(t_env *head);
void	print_lst(t_env *lst);

char	*get_pwd(void);
t_env	*search_pwd(t_env *lst);

int		get_args_len(t_cmd *cmd_lst);
int		get_lst_len(t_env *lst);
int		iter_diff(t_env *lst, t_env *new_node);
size_t	get_cmd_len(t_cmd *cmd);	

/**
 * EXECUTING FUNCTIONS
 */
void	exec_sys(t_env *lst, t_cmd *cmd_lst);
void	main_child(t_env *lst, t_cmd *cmd_lst, char *path);
char	**get_path(t_env *lst);
char	*check_access(t_env *lst, t_cmd *cmd_lst);
char	**lst_to_char(t_env *lst);

void	redirect(t_env *lst, t_cmd *cmd_lst, int flag, int status);
void	exec(t_env *lst, t_cmd *cmd_lst, int status, char *file);

void	exec_pipe(t_env *lst, t_cmd *cmd_lst);
size_t	exec_builtin(t_env *lst, t_cmd *cmd_lst);
void	exec_alone(t_cmd *cmd_lst, t_env *lst, ssize_t *id, char *path);
void	exec_sys(t_env *lst, t_cmd *cmd_lst);
void	pipe_exec(t_env *lst, t_cmd *cmd_lst, int (*fd)[2], ssize_t *id, size_t len, size_t i, size_t flag);
void	fork_arr(t_env *lst, t_cmd *cmd_lst, int (*fd)[2], ssize_t *id);
void	loop_lst(t_env *lst, t_cmd **cmd_lst, size_t len, int (*fd)[2], ssize_t *id, size_t flag);
void	pipe_arr(int (*fd)[2], size_t i);
void	close_pipes(int (*fd)[2], size_t i, size_t len);
size_t	check_builtin(t_cmd *cmd_lst);
size_t	check_path(t_cmd *cmd_lst, char *path, size_t *flag);
size_t	check_all_path(t_env *lst, t_cmd *cmd_lst);
void	main_child2(t_cmd *cmd_lst, char *path, char **env_kid);
void	check_pos(t_env *lst, t_cmd *cmd_lst, int (*fd)[2], size_t len, size_t i, size_t flag);

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
void	free_exec(int (*fd)[2], ssize_t *id);

void	new_prompt(int val);

/**
 * ERROR FUNCTONS
 */
void	export_error(char *val);

int		ft_strcmp(const char *s1, const char *s2);

#endif
