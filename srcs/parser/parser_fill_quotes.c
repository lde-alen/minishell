/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:02:04 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/04 17:27:05 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fill_quotes(char *str, char quote, t_msh *msh)
{
	while (str[msh->sh->i] != quote && msh->sh->i < ft_strlen(str))
	{
		if (str[msh->sh->i] == '$' && msh->sh->dq == 1)
			ft_fill_expand(str, msh);
		else
			msh->sh->tmp_str[msh->sh->j] = str[msh->sh->i];
		msh->sh->j++;
		msh->sh->i++;
	}
	msh->sh->j++;
	msh->sh->i++;
	if (quote == '"')
		msh->sh->dq = 0;
	else if (quote == '\'')
		msh->sh->sq = 0;
}	
