/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:05:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/08 15:09:55 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//signal handler for ^C
void	sig_handler(int val)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit = 1;
	signal(val, sig_handler);
}

void	shell_prompt(char **env)
{
	char	*str;
	t_env	*lst;
	t_cmd	*cmd_lst;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&lst, 0, sizeof(t_env *));
	ft_memset(&cmd_lst, 0, sizeof(t_cmd *));
	lst = ft_env(env);
	while (1)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			if (ft_strlen(str) > 1)
			{
				add_history(str);
				cmd_lst = ft_cmd_lst(str);
				ft_parse(lst, cmd_lst);
				// free_cmd(cmd_lst);
			}
		}
		else
		{
			free_env_lst(lst);
			// free_cmd(cmd_lst);
			exit(0);
		}
	}
}
