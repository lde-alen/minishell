/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_quotes_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:18:43 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/18 23:26:30 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_quote_loop(char quote, t_lex *lex, char *str)
{
	while (str[lex->sh->i] != quote && str[lex->sh->i])
	{
		if (str[lex->sh->i] == '$' && lex->sh->dq == 1
			&& ((ft_isalnum(str[lex->sh->i + 1])
					|| (str[lex->sh->i + 1] == '"'
						|| str[lex->sh->i + 1] == '\''
						|| str[lex->sh->i + 1] == '?'))))
			ft_fill_expand(str, lex);
		else
		{
			lex->sh->tmp_str[lex->sh->j] = str[lex->sh->i];
			lex->sh->j++;
		}
		lex->sh->i++;
	}
}

void	args_to_init(char **tmp, size_t *i)
{
	*tmp = (char *)ft_calloc(1, sizeof(char));
	*i = 0;
}
