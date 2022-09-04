/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:02:04 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/04 23:15:56 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fill_quotes(char *str, char quote, t_msh *msh)
{
	if (quote == '"')
		msh->sh->dq = 1;
	msh->sh->i++;
	while (str[msh->sh->i] != quote && msh->sh->i < ft_strlen(str))
	{
		if (str[msh->sh->i] == '$' && msh->sh->dq == 1)
			ft_fill_expand(str, msh);
		else
			msh->sh->tmp_str[msh->sh->j] = str[msh->sh->i];
		msh->sh->j++;
		msh->sh->i++;
	}
	msh->sh->j--;
	msh->sh->dq = 0;
}	
