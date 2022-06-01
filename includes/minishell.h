/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:25:16 by lde-alen          #+#    #+#             */
/*   Updated: 2022/06/01 14:58:08 by asanthos         ###   ########.fr       */
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

typedef struct s_echo
{
	char			*args;
	struct s_echo	*next;
}	t_echo;

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
void	exec_cmd(char *str, t_env *lst);
int		minishell(int ac, char **av, char **env);
void	ft_echo(char *str);
t_env	*ft_env(char **env);
void	print_list_env(t_env *head);
t_env	*push_env(t_env *lst, char *env_name, char *env_value);
void	ft_expander(t_env *lst, char *str);
void    ft_lst_init(char *str);
void    ft_pwd(t_env *lst);
void	ft_parse(char *str, t_env *lst);

#endif
