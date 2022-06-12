/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:05:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/11 05:21:15 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_prompt(int i)
{
	(void)i;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	shell_prompt(char **env)
{
	char	*str;
	t_env	*lst;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	lst = ft_env(env);
	while (1)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			if(ft_strlen(str) > 1)
			{
				add_history(str);
				ft_parse(str, lst);
			}
		}
		else
			exit(0);
	}
}
