/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:25:16 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/20 16:43:58 by lde-alen         ###   ########.fr       */
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
# define NOTHING	0
# define R_REDIR	1
# define L_REDIR	2
# define DR_REDIR	3
# define DL_REDIR	4

/**
 * Defining your tools and refining them is the key
 */

// int *flag;
// i = 5; = flag_len
// while i <= flag_len
// 	i++

// flag[0] = R_REDIR					file[0] = file name 1
// flag[1] = R_REDIR					file[1] = file name 2
// flag[2] = R_REDIR					file[2]	= file name 3
// flag[5] = L_REDIR
// flag[3] = R_REDIR
// flag[4] = R_REDIR
// flag[6] = R_REDIR

// flag_len;

//not using
typedef struct s_redir
{
	size_t		r_flag;
	size_t		**flag;
	size_t		flag_len;

}	t_redir;

// split by pipes / arg / command / str / next /
typedef struct s_cmd
{
	char			**argument;
	char			*command;
	char			*str;
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

typedef struct s_msh
{
	t_redir	*redir;
	t_env	*env;
	t_sh	*sh;
	t_cmd	*cmd;
}	t_msh;

/**
 * Teaching kinds how to manipulate tools
 */
void	ft_print_char_arr(char **array);
void	print_list_env(t_env *head);
void	ft_expand(t_env *lst, char *str);
void	new_prompt(int val);
void	ft_expand(t_env *lst, char *str);

char	*ft_append_char(char *name, char c);

int		minishell(char **env);
int		ft_init(t_cmd **cmd, t_env **env);
int		ft_parse(char *str, t_msh *msh);
int		ft_fill_arg(char ***argument, char *str);
int		ft_fill_cmd(char **command, char **argument);
int		check_redirections(char *str, t_sh *sh);
int		check_quotes(char *str, char quote, t_sh *sh);
int		parser_stage1(char *str, t_sh *sh);
int		parser_stage2(char *str, t_msh *msh);
int		ft_check_expand(char *str, t_sh *sh, t_env *env);
int		check_p(char *str);
int		check_fill_redirections(char *str, t_msh *msh);
int		check_fill_quotes(char *str, char c, t_msh *msh);

t_env	*push_lst(t_env *new, t_env *lst, char *env_name, char *env_value);
t_env	*push_env(t_env *env_list, char *env_name, char *env_value);
t_env	*ft_env(char **env);

#endif
