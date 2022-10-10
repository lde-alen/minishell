/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:02:04 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/10 16:04:53 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fill_quotes(char *str, char quote, t_lex *lex)
{
	if (quote == '"')
		lex->sh->dq = 1;
	while (lex->sh->i <= ft_strlen(str))
	{
		if (str[lex->sh->i] == '$' && lex->sh->dq == 1)
			ft_fill_expand(str, lex);
		else
			lex->sh->tmp_str[lex->sh->j] = str[lex->sh->i];
		lex->sh->j++;
		lex->sh->i++;
	}
	lex->sh->j--;
	lex->sh->dq = 0;
}	
