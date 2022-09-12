/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:43:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/12 12:04:18 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **env)
{
	t_lex	*lex;
	char	*str;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	lex = (t_lex *)malloc(sizeof(t_lex));
	ft_memset(&lex->env, 0, sizeof(t_env *));
	lex->env = ft_env(env);
	while (42)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			add_history(str);
			ft_parse(str, lex);
		}
		else
			exit(EXIT_FAILURE);
	}
}
