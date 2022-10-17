/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:02:04 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/14 19:55:03 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fill_quotes(char *str, char quote, t_lex *lex)
{
	if (quote == '"')
	{
		lex->sh->tmp_str[lex->sh->j] = D_QUOTE;
		lex->sh->dq = 1;
	}
	else if (quote == '\'')
		lex->sh->tmp_str[lex->sh->j] = S_QUOTE;
	lex->sh->j++;
	lex->sh->i++;
	while (str[lex->sh->i] != quote && str[lex->sh->i])
	{
		if (str[lex->sh->i] == '$' && lex->sh->dq == 1)
			ft_fill_expand(str, lex);
		else
		{
			lex->sh->tmp_str[lex->sh->j] = str[lex->sh->i];
		}
		lex->sh->j++;
		lex->sh->i++;
	}
	if (str[lex->sh->i] == quote && quote == '"')
		lex->sh->tmp_str[lex->sh->j] = D_QUOTE;
	else if (str[lex->sh->i] == quote && quote == '\'')
		lex->sh->tmp_str[lex->sh->j] = S_QUOTE;
	lex->sh->dq = 0;
}	
