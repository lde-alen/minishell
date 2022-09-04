/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 13:02:04 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/04 22:58:59 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fill_quotes(char *str, char quote, t_msh *msh)
{
	msh->sh->i++;
	while (str[msh->sh->i] != quote && msh->sh->i < ft_strlen(str))
	{
		// ft_printf("current char is: %c\n", str[msh->sh->i]);
		if (str[msh->sh->i] == '$' && msh->sh->dq == 1)
		{
			msh->sh->i++;
			ft_fill_expand(str, msh);
		}
		else
		{
			// ft_printf("else\n");
			// ft_printf("current i: %d\n", msh->sh->i);
			// ft_printf("current j: %d\n", msh->sh->j);
			// ft_printf("j char is: %c\n", msh->sh->tmp_str[msh->sh->j]);
			msh->sh->tmp_str[msh->sh->j] = str[msh->sh->i];

		}
		msh->sh->j++;
		msh->sh->i++;
	}
}	
