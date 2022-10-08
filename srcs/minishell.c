/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:43:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/08 15:00:40 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int val)
{
	if (val == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		g_exit = 130;
	}
}

int	minishell(char **env)
{
	t_lex	*lex;
	char	*str;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	lex = (t_lex *)malloc(sizeof(t_lex));
	if (!lex)
	{
		free_child(lex);
		exit(0);
	}
	ft_memset(&lex->env, 0, sizeof(t_env *));
	lex->env = ft_env(env);
	while (42)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			if (ft_strlen(str) >= 1)
			{
				add_history(str);
				if (ft_parse(str, lex) == 0)
				{
					// ft_print_char_arr(lex->cmd->argument);
					exec_sys(lex);
				}
			}
		}
		else
		{
			if (lex->cmd)
			{
				if (lex->cmd->redir)
					free_child(lex);
			}
			else
			{
				free_env_lst(lex->env);
				free (lex);
			}
			exit(0);
		}
	}
}
