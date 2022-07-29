/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:05:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/29 19:09:06 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_prompt(int val)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit (val);
}

void	shell_prompt(char **env)
{
	char	*str;

	(void)env;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			if (ft_strlen(str) > 1)
			{
				add_history(str);
				ft_parse(str, env);
			}
		}
		else
			exit(0);
	}
}
