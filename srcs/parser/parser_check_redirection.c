/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:00:06 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/21 00:37:30 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*/
int	check_redirections(char *str, t_sh *sh)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			sh->dq = 1;
			i++;
			while (str[i] != '"' && str[i])
				i++;
		}
		else if (str[i] == '\'')
		{
			sh->sq = 1;
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		else if (str[i] == '>')
		{
			i++;
			sh->sr = 1;
			while (str[i] == '>' && str[i])
			{
				sh->sr++;
				i++;
			}
			if (sh->sr > 2)
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
			i--;
		}
		else if (str[i] == '<')
		{
			i++;
			sh->sr = 1;
			while (str[i] == '<' && str[i])
			{
				sh->sr++;
				i++;
			}
			if (sh->sr > 2)
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
			i--;
		}
		else if (str[i] == '|')
		{
			sh->p = 1;
			if (i == 0)
			{
				ft_putstr_fd("ERROR PIPE\n", 2);
				return (1);
			}
			while (str[i] == ' ' && str[i])
				i++;
			if (!(str[i] > ' ' && str[i] <= '~')
				|| str[i] == '>' || str[i] == '<' || str[i] == '|')
			{
				ft_putstr_fd("ERROR PIPE\n", 2);
				return (1);
			}
			i--;
		}
	}
	return (0);
}
