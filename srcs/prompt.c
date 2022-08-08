/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:05:25 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/08 19:14:52 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_env	*env_lst;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&env_lst, 0, sizeof(t_env));
	env_lst = ft_env(env);
	while (42)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			add_history(str);
			ft_parse(str, env_lst);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}
}
