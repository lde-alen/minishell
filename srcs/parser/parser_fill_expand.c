/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:52:13 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/04 11:54:41 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_expand(char *str, t_msh *msh)
{
	char	*name;

	name = (char *)malloc(sizeof(char) * 1);
	name[0] = '\0';
	msh->sh->i++;
	if ((ft_isdigit(str[msh->sh->i]) == 1)
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
		ft_strjustcat(msh->sh->tmp_str, get_env_value(msh->env, name));
		msh->sh->j += (ft_strlen(get_env_value(msh->env, name) - 1));
	}
	free (name);
}
