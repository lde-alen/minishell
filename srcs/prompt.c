/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:05:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/05/26 23:51:34 by lde-alen         ###   ########.fr       */
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

void	shell_prompt(void)
{
	char	*str;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			add_history(str);
			exec_cmd(str);
		}
		else
			exit(0);
	}
}
