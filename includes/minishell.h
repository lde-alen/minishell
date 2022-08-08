/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:25:16 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/08 19:42:08 by lde-alen         ###   ########.fr       */
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
	char			**argument;
	char			*command;
	char			*str;
	int				q_flag;
	int				p_flag;
	int				r_flag;
	int				cash_flag;
	int				token;
	unsigned int	side;
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
	char			*input;
	size_t			euro;
	size_t			sq;
	size_t			dq;
	size_t			sr;
}	t_sh;

typedef enum e_boolean
{
	false,
	true
}	t_bool;

/**
 * Teaching kinds how to manipulate tools
 */
void	shell_prompt(char **env);
void	ft_print_char_arr(char **array);
int		minishell(char **env);
int		ft_init(t_cmd **cmd, t_env **env);
int		ft_parse(char *str, t_env *env_lst);
int		ft_fill_arg(char ***argument, char *str);
int		ft_fill_cmd(char **command, char **argument);
int		check_redirections(char *str, t_sh *sh);
int		check_quotes(char *str, char quote, t_sh *sh);
t_env	*push_env(t_env *env_list, char *env_name, char *env_value);
t_env	*ft_env(char **env);
void	ft_expand(t_env *lst, char *str);
t_env	*push_lst(t_env *new, t_env *lst, char *env_name, char *env_value);
int		parser_stage1(char *str, t_sh *sh);
int		parser_stage2(char *str, t_sh *sh, t_env *env);
int		ft_check_expand(char *str, t_sh *sh, t_env *env);
int		check_p(char *str);
void	print_list_env(t_env *head);

#endif
