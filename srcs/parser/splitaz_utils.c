/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitaz_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:36:37 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/18 18:33:21 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_len_loop(char const **s, size_t *len, int quote)
{
	if (**s == quote)
	{
		(*s)++;
		(*len)++;
		while (**s && **s != quote)
		{
			(*s)++;
			(*len)++;
		}
		if (**s)
		{
			(*s)++;
			(*len)++;
		}
	}
}

int	free_splitaz_tab(char **tab, size_t *i)
{
	while (*i)
		free(tab[--(*i)]);
	free(tab);
	return (1);
}

void	splitaz_loop(char const **s, size_t *len)
{
	if (**s == D_QUOTE)
		quote_len_loop(s, len, D_QUOTE);
	else if (**s == S_QUOTE)
		quote_len_loop(s, len, S_QUOTE);
	else
	{
		(*len)++;
		(*s)++;
	}
}
