/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:00:33 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/03 12:37:21 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_p(char *str, t_msh *msh)
{
	if (str[msh->sh->i] == '|')
	{
		msh->sh->p = 1;
		if (msh->sh->i == 0)
		{
			ft_putstr_fd("ERROR PIPE\n", 2);
			return (1);
		}
		msh->sh->i++;
		while (str[msh->sh->i] == ' ' && str[msh->sh->i])
			msh->sh->i++;
		if (str[msh->sh->i] == '|' || msh->sh->i == ft_strlen(str))
		{
			ft_putstr_fd("ERROR PIPE\n", 2);
			return (1);
		}
		if (!(str[msh->sh->i] > ' ' && str[msh->sh->i] <= '~')
			|| str[msh->sh->i] == '>' || str[msh->sh->i] == '<'
			|| str[msh->sh->i] == '|')
		{
			ft_putstr_fd("ERROR PIPE\n", 2);
			return (1);
		}
		msh->sh->i--;
	}
	return (0);
}
