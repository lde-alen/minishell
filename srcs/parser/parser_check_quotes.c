/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:59:05 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/04 22:41:52 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str, char quote, t_msh *msh)
{
	if (str[msh->sh->i] == '\'')
		msh->sh->sq += 1;
	if (str[msh->sh->i] == '"')
		msh->sh->dq += 1;
	msh->sh->i++;
	if (str[msh->sh->i] && ft_strchr((str + msh->sh->i), quote) != NULL)
	{
		while (str[msh->sh->i] != quote && str[msh->sh->i])
		{
			if (str[msh->sh->i] == '$' && quote == '"')
				ft_check_expand(str, msh);
			msh->sh->i++;
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
