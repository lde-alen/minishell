/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:00:06 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/26 14:50:30 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*/
int	check_redirections(char *str, t_msh *msh)
{
	size_t	i;
	char	*name;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
		{
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == '|')
			{
				ft_putstr_fd("ERROR REDIR\n", 2);
				return (1);
			}
		}
		if (str[i] == '"')
		{
			msh->sh->dq = 1;
			i++;
			while (str[i] != '"' && str[i])
			{
				if (str[msh->sh->i] == '$')
				{
					name = ft_calloc(2, sizeof(char));
					name[0] = '$';
					msh->sh->i++;
					if ((ft_isdigit(str[msh->sh->i]) == 1)
						&& str[msh->sh->i - 1] == '$')
						msh->sh->i++;
					else
					{
						while (str[msh->sh->i] && str[msh->sh->i] != '$'
							&& ft_isalnum(str[msh->sh->i]) == 1)
						{
							name = ft_append_char(name, str[msh->sh->i]);
							msh->sh->i++;
						}
						ft_expand(msh->env, name);
						msh->sh->i--;
					}
					free(name);
				}
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
			i--;
		}
		else if (str[i] == '|')
		{
			msh->sh->p = 1;
			if (i == 0)
			{
				ft_putstr_fd("ERROR PIPE\n", 2);
				return (1);
			}
			i++;
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
