/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:00:06 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/18 10:18:44 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*/
int	check_redirections(char *str, t_lex *lex)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
		}
		if (str[i] == '"')
		{
			lex->sh->dq = 1;
			i++;
			while (str[i] != '"' && str[i])
			{
				if (str[i] == '$')
					ft_check_expand(str, lex);
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			lex->sh->sq = 1;
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		else if (str[i] == '>')
		{
			i++;
			lex->sh->sr = 1;
			while (str[i] == '>' && str[i])
			{
				lex->sh->sr++;
				i++;
			}
			if (lex->sh->sr > 2)
			{
				ft_putstr_fd("ERROR REDIR\n", 2);
				return (1);
			}
			while (str[i] == ' ' && str[i])
				i++;
			if (!(str[i] > ' ' && str[i] <= '~')
				|| str[i] == '<' || str[i] == '>' || str[i] == '|')
			{
				ft_putstr_fd("ERROR REDIR\n", 2);
				return (1);
			}
			if (str[i] == '$')
				ft_check_expand(str, lex);
			i--;
		}
		else if (str[i] == '<')
		{
			i++;
			lex->sh->sr = 1;
			while (str[i] == '<' && str[i])
			{
				lex->sh->sr++;
				i++;
			}
			if (lex->sh->sr > 2)
			{
				ft_putstr_fd("ERROR REDIR\n", 2);
				return (1);
			}
			while (str[i] == ' ' && str[i])
				i++;
			if (!(str[i] > ' ' && str[i] <= '~')
				|| str[i] == '>' || str[i] == '<' || str[i] == '|')
			{
				ft_putstr_fd("ERROR REDIR\n", 2);
				return (1);
			}
			if (str[i] == '$')
				ft_check_expand(str, lex);
			i--;
		}
		i++;
	}
	return (0);
}
