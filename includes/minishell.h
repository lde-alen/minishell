/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:25:16 by lde-alen          #+#    #+#             */
/*   Updated: 2022/07/25 10:58:52 by asanthos         ###   ########.fr       */
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
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

/**
 * Teaching kinds how to manipulate tools
 */
void	shell_prompt(char **env);
t_env	*push_env(t_env *lst, char *env_name, char *env_value);
t_env	*push_lst(t_env *new, t_env *lst, char *env_name, char *env_value);
void	exec_cmd(t_env *lst, t_cmd *cmd_lst);
int		minishell(int ac, char **av, char **env);

t_env	*ft_env(char **env);
void	ft_echo(t_cmd *cmd_lst);
void	ft_pwd(t_env *lst);
void	ft_export(t_env *lst, t_cmd *cmd_lst);
void	ft_unset(t_env *lst, t_cmd *cmd_lst);
void	ft_cd(t_cmd *cmd_lst, t_env *lst);

void	print_list_env(t_env *head);
void	ft_expander(t_env *lst, char *str);
t_cmd	*ft_lst_init(char *str);
char    *get_pwd();
t_env   *search_pwd(t_env *lst);
void	ft_parse(char *str, t_env *lst);
void    free_split(char **split_cmd);
// void	div_env(char *str, t_env *lst);

void	lst_free(t_cmd *cmd_lst, t_env *lst);
void	free_env_lst(t_env *lst);
void	lonely_export(t_env *lst);

void	check_exec(t_env *lst, t_cmd *cmd_lst);
void	pipes(t_env *lst, t_cmd *cmd_lst);

#endif
