/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:52:13 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/18 23:12:19 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_expand(char *str, t_lex *lex)
{
	char	*name;
	char	*ascii_exit;

	ascii_exit = NULL;
	name = ft_calloc(1, sizeof(char));
	lex->sh->i++;
	if ((ft_isdigit(str[lex->sh->i]) == 1)
		&& (ft_isdigit(str[lex->sh->i + 1]) == 1))
			lex->sh->i++;
	else if (str[lex->sh->i] == '?')
	{
		question_assist(&name, ascii_exit, lex, str);
	}
	else
	{
		setup_expand(lex, &name, str);
		lex->sh->j++;
	}
	free (name);
}
