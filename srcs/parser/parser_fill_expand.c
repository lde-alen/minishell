/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:52:13 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/04 00:42:04 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_expand(char *str, t_msh *msh)
{
	char	*name;

	name = "";
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
			msh->sh->j++;
		}
		msh->sh->expand_len += get_expand_len(name, msh->env);
		ft_strjustcat(msh->sh->tmp_str, ft_expand(msh->env, name));
		msh->sh->j += (ft_strlen(ft_expand(msh->env, name)) - 1);
		// free(name);
	}
}
