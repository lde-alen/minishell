/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:52:13 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/09 18:32:00 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_expand(char *str, t_lex *lex)
{
	char	*name;

	name = ft_calloc(1, sizeof(char));
	lex->sh->i++;
	if ((ft_isdigit(str[lex->sh->i]) == 1)
		&& (ft_isdigit(str[lex->sh->i + 1]) == 1))
			lex->sh->i++;
	else if (str[lex->sh->i] == '?')
	{
		name = ft_append_char(name, str[lex->sh->i]);
		lex->sh->expand_len += get_expand_len(name, lex->env, 1);
		lex->sh->j += ft_strlen(ft_itoa(g_exit));
		ft_strjustcat(lex->sh->tmp_str, ft_itoa(g_exit));
	}
	else
	{
		while (str[lex->sh->i] && str[lex->sh->i] != '$'
			&& ft_isalnum(str[lex->sh->i]) == 1)
		{
			name = ft_append_char(name, str[lex->sh->i]);
			lex->sh->i++;
		}
		lex->sh->i--;
		lex->sh->expand_len += get_expand_len(name, lex->env, 0);
		lex->sh->j += (ft_strlen(get_env_value(lex->env, name)) - 1);
		ft_strjustcat(lex->sh->tmp_str, get_env_value(lex->env, name));
	}
	free (name);
}
