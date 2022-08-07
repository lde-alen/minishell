/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:59:05 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/07 23:35:02 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str, char quote, t_sh *sh)
{
	if (str[sh->i] == '\'' || str[sh->i] == '"')
	{
		if (str[sh->i] == '\'')
			sh->sq += 1;
		if (str[sh->i] == '"')
			sh->dq += 1;
		if ((quote == '\'' && sh->dq == 0) || (quote == '"' && sh->sq == 0))
		{
			sh->i++;
			if (str[sh->i] && ft_strchr((str + sh->i), quote) != NULL)
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
