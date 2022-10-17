/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:43:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/17 15:59:56 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(char **env)
{
	t_lex	*lex;
	char	*str;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	lex = (t_lex *)malloc(sizeof(t_lex));
	if (!lex)
		exit(EXIT_FAILURE);
	ft_memset(&lex->env, 0, sizeof(t_env *));
	lex->env = ft_env(env);
	while (42)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		mini_loop(lex, str);
	}
}
