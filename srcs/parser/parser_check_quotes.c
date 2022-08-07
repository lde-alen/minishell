/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:59:05 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/07 18:34:40 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str, char quote, t_sh *sh)
{
	size_t	sq;
	size_t	dq;

	sq = 0;
	dq = 0;
	if (str[sh->i] == '\'' || str[sh->i] == '"')
	{
		if (str[sh->i] == '\'')
			sq += 1;
		if (str[sh->i] == '"')
			dq += 1;
		if ((quote == '\'' && dq == 0) || (quote == '"' && sq == 0))
		{
			if (ft_strchr(str + ++sh->i, quote) != NULL)
			{
				while (str[sh->i] != quote && str[sh->i])
					sh->i++;
			}
			else
			{
				if (quote == '\'')
					ft_putstr_fd("Error: Missing quote... RTFPDF.\n", 2);
				if (quote == '"')
					ft_putstr_fd("Error: missing dquote... RTFPDF\n", 2);
				return (1);
			}
		}
	}
	return (0);
}
