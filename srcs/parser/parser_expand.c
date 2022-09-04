/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:44:32 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/04 15:47:17 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_expand(char *str, t_msh *msh)
{
	char	*name;

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
	return (0);
}
