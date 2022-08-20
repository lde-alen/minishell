/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:43:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/20 14:22:02 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **env)
{
	t_msh	*msh;
	char	*str;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	msh = (t_msh *)malloc(sizeof(t_msh));
	ft_memset(&msh->env, 0, sizeof(t_env *));
	msh->env = ft_env(env);
	while (42)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			add_history(str);
			ft_parse(str, msh);
		}
		else
			exit(EXIT_FAILURE);
	}
}
