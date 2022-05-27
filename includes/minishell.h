/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:25:16 by lde-alen          #+#    #+#             */
/*   Updated: 2022/05/27 20:55:54 by asanthos         ###   ########.fr       */
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
	char			*path;
	char			*command;
	char			**argument;
	struct s_cmd	*next;
	int				token;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_ms
{
	t_env	*env;
	t_cmd	*cmd;
	t_echo	*echo;
}	t_ms;

/**
 * Teaching kinds how to manipulate tools
 */
void	shell_prompt(char *env[]);
void	exec_cmd(char *str, char *env[]);
void	ft_expander(char *str, char *env[]);
void	ft_echo(char *str);
int		minishell(int ac, char **av, char **env);

#endif
