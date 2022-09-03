/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:02:04 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/03 22:22:06 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fill_quotes(char *str, char quote, t_msh *msh)
{
	if (str[msh->sh->i] == '\'' || str[msh->sh->i] == '"')
	{
		if (str[msh->sh->i] == '\'')
			msh->sh->sq += 1;
		if (str[msh->sh->i] == '"')
			msh->sh->dq += 1;
		if ((quote == '\'' && msh->sh->dq == 0)
			|| (quote == '"' && msh->sh->sq == 0))
		{
			if ((quote == '\'' && msh->sh->dq == 0) || (quote == '"' && msh->sh->sq == 0))
			{
				msh->sh->i++;
				while (str[msh->sh->i] != quote && str[msh->sh->i])
				{
					if (str[msh->sh->i] == '$' && quote == '"')
						ft_fill_expand(str, msh);
					msh->sh->tmp_str[msh->sh->j] = str[msh->sh->i];
					msh->sh->j++;
					msh->sh->i++;
				}
				msh->sh->i++;
			}
		}
	}
}	
