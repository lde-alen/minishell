/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:43:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/14 01:12:21 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **env)
{
	char	*str;
	t_env	*env_lst;
	t_cmd	*cmd;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(&env_lst, 0, sizeof(t_env *));
	env_lst = ft_env(env);
	while (42)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			add_history(str);
			ft_parse(str, env_lst, cmd);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}
}
