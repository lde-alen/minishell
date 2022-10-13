/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:44:32 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/13 18:36:18 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_expand(char *str, t_lex *lex)
{
	char	*name;

	name = ft_calloc(2, sizeof(char));
	name[0] = '$';
	lex->sh->i++;
	if ((ft_isdigit(str[lex->sh->i]) == 1)
		&& str[lex->sh->i - 1] == '$'
		&& (ft_isdigit(str[lex->sh->i + 1]) == 1))
		lex->sh->i++;
	else
	{
		while (str[lex->sh->i] && str[lex->sh->i] != '$'
			&& ft_isalnum(str[lex->sh->i]) == 1)
		{
			name = ft_append_char(name, str[lex->sh->i]);
			lex->sh->i++;
		}
		lex->sh->expand_len += get_expand_len(name, lex->env, 0);
		ft_expand(lex->env, name);
	}
	lex->sh->i--;
	free(name);
	return (0);
}
