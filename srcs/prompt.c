/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:05:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/05/25 10:53:48 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	new_prompt()
{
	char *p_buff;

	p_buff = (char *)malloc(sizeof(char) * 1000);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	printf("\e[0;37m|🐼| \e[0;35mminishell\e[0;37m | \e[0;34m%s\e[0;37m$\e[0m ", getcwd(p_buff, 1000));
	free(p_buff);
	rl_on_new_line();
	rl_redisplay();
}

void	shell_prompt(void)
{
	char	*p_buff;
	char	*str;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		//fix malloc
	    p_buff = (char *)malloc(sizeof(char) * 1000);
		printf("\e[0;37m|🐼| \e[0;35mminishell\e[0;37m | \e[0;34m%s\e[0;37m$\e[0m ", getcwd(p_buff, 1000));
		free(p_buff);
		str = readline("");
		if (!str)
			exit(0);
	}
}
