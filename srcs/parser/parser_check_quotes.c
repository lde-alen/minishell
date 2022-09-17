/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:59:05 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/17 17:16:14 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str, char quote, t_lex *lex)
{
	if (str[lex->sh->i] == '\'')
		lex->sh->sq += 1;
	if (str[lex->sh->i] == '"')
		lex->sh->dq += 1;
	lex->sh->i++;
	if (str[lex->sh->i] && ft_strchr((str + lex->sh->i), quote) != NULL)
	{
		while (str[lex->sh->i] != quote && str[lex->sh->i])
		{
			if (str[lex->sh->i] == '$' && quote == '"')
				ft_check_expand(str, lex);
			lex->sh->i++;
		}
	}
	else
	{
		if (quote == '\'')
			ft_putstr_fd("Error: Missing quote... RTFPDF.\n", 2);
		if (quote == '"')
			ft_putstr_fd("Error: missing dquote... RTFPDF\n", 2);
		return (1);
	}
	return (0);
}
