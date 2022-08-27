/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:00:06 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/27 23:09:14 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*/
int	check_redirections(char *str, t_msh *msh)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
		}
		if (str[i] == '"')
		{
			msh->sh->dq = 1;
			i++;
			while (str[i] != '"' && str[i])
			{
				if (str[i] == '$')
					ft_check_expand(str, msh);
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			msh->sh->sq = 1;
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		else if (str[i] == '>')
		{
			i++;
			msh->sh->sr = 1;
			while (str[i] == '>' && str[i])
			{
				msh->sh->sr++;
				i++;
			}
			if (msh->sh->sr > 2)
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
				ft_check_expand(str, msh);
			i--;
		}
		else if (str[i] == '<')
		{
			i++;
			msh->sh->sr = 1;
			while (str[i] == '<' && str[i])
			{
				msh->sh->sr++;
				i++;
			}
			if (msh->sh->sr > 2)
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
				ft_check_expand(str, msh);
			i--;
		}
	}
	return (0);
}
