/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:59:05 by lde-alen          #+#    #+#             */
/*   Updated: 2022/08/07 01:00:23 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str, char quote)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == quote)
		{
			if (ft_strchr(str + ++i, quote) != NULL)
			{
				while (str[i] != quote && str[i])
					i++;
			}
			else
			{
				if (quote == '\'')
					ft_putstr_fd("Error: Missing quote... RTFPDF.\n", 2);
				else if (quote == '"')
					ft_putstr_fd("Error: missing dquote... RTFPDF", 2);
				return (1);
			}
		}
	}
	return (0);
}
