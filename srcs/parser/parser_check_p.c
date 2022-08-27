/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:00:33 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/27 23:09:10 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_p(char *str, t_msh *msh)
{
	char	*name;

	if (str[msh->sh->i] == '|')
	{
		msh->sh->p = 1;
		if (msh->sh->i == 0)
		{
			ft_putstr_fd("ERROR PIPE\n", 2);
			return (1);
		}
		msh->sh->i++;
		while (str[msh->sh->i] == ' ' && str[msh->sh->i])
			msh->sh->i++;
		if (str[msh->sh->i] == '|' || msh->sh->i == ft_strlen(str))
		{
			ft_putstr_fd("ERROR PIPE\n", 2);
			return (1);
		}
		if (str[msh->sh->i] == '$')
		{
			name = ft_calloc(2, sizeof(char));
			name[0] = '$';
			msh->sh->i++;
			if ((ft_isdigit(str[msh->sh->i]) == 1)
				&& str[msh->sh->i - 1] == '$'
				&& (ft_isdigit(str[msh->sh->i + 1]) == 1))
				msh->sh->i++;
			else
			{
				while (str[msh->sh->i] && str[msh->sh->i] != '$'
					&& ft_isalnum(str[msh->sh->i]) == 1)
				{
					name = ft_append_char(name, str[msh->sh->i]);
					msh->sh->i++;
				}
				msh->sh->expand_len += get_expand_len(name, msh->env);
				ft_expand(msh->env, name);
				msh->sh->i--;
			}
			free(name);
		}
		if (!(str[msh->sh->i] > ' ' && str[msh->sh->i] <= '~')
			|| str[msh->sh->i] == '>' || str[msh->sh->i] == '<' || str[msh->sh->i] == '|')
		{
			ft_putstr_fd("ERROR PIPE\n", 2);
			return (1);
		}
		msh->sh->i--;
	}
	return (0);
}
