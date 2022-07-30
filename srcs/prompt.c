/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:05:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/30 03:36:17 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_prompt(int val)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit(val);
}

void	shell_prompt(char **env)
{
	char	*str;
	t_env	*lst;
	t_cmd	*cmd_lst;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&lst, 0, sizeof(lst));
	ft_memset(&cmd_lst, 0, sizeof(cmd_lst));
	lst = ft_env(env);
	while (1)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			if(ft_strlen(str) > 1)
			{
				add_history(str);
				cmd_lst = ft_lst_init(str);
				ft_parse(lst, cmd_lst);
				free(cmd_lst->argument);
				free(cmd_lst);
				// free_cmd(cmd_lst);
			}
		}
		else
		{
			free_env_lst(lst);
			exit(0);
		}
	}
}
