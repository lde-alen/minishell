/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:25:16 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/11 04:43:20 by lde-alen         ###   ########.fr       */
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
/**
 * Alka perfect input:
 * 		- char **argument must have in arg[0] the cmd and the rest 
 * 	should be the arguments even with args after redirections
 * 
 * 		- char *command will contain only the command without arguments
 * 
 * 		- char **flag will will contain redirections in their respective orders 
 * 	and on the sam
 * 
 */

typedef struct s_redir
{
	char		**file;
	size_t		r_flag;
	size_t		*flag;
	size_t		flag_len;
	size_t		ll;
	size_t		lr;
	size_t		rr;

}	t_redir;

// split by pipes / arg / command / str / next /
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
ssize_t	get_expand_len(char *name, t_env *env);
char	*get_env_value(t_env *env, char *name);
char	*ft_append_char(char *name, char c);
void	ft_fill_expand(char *str, t_msh *msh);
void	ft_print_char_arr(char **array);
void	print_list_env(t_env *head);
char	*ft_expand(t_env *lst, char *str);
void	new_prompt(int val);
void	ft_strjustcat(char *dst, const char *src);
int		minishell(char **env);
int		ft_init(t_cmd **cmd, t_env **env);
int		ft_parse(char *str, t_msh *msh);
void	ft_fill_arg(t_msh *msh);
int		check_redirections(char *str, t_msh *msh);
int		check_quotes(char *str, char quote, t_msh *msh);
int		parser_stage1(char *str, t_msh *msh);
int		parser_stage2(char *str, t_msh *msh);
int		ft_check_expand(char *str, t_msh *msh);
int		check_p(char *str, t_msh *msh);
void	check_fill_redirections(char *str, t_msh *msh);
void	check_fill_quotes(char *str, char c, t_msh *msh);
void	ft_fill_redir(t_msh *msh);
t_env	*push_lst(t_env *new, t_env *lst, char *env_name, char *env_value);
t_env	*push_env(t_env *env_list, char *env_name, char *env_value);
t_env	*ft_env(char **env);
void	ft_fill_command(char **tab, size_t i, t_msh *msh);
void	ft_fill_arg(t_msh *msh);
void	ft_append_back(char **str, char c);

#endif
