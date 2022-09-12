/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_p.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 19:00:33 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/12 12:01:51 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_p(char *str, t_lex *lex)
{
	if (str[lex->sh->i] == '|')
	{
		lex->sh->p = 1;
		if (lex->sh->i == 0)
		{
			ft_putstr_fd("ERROR PIPE\n", 2);
			return (1);
		}
		lex->sh->i++;
		while (str[lex->sh->i] == ' ' && str[lex->sh->i])
			lex->sh->i++;
		if (str[lex->sh->i] == '|' || lex->sh->i == ft_strlen(str))
		{
			ft_putstr_fd("ERROR PIPE\n", 2);
			return (1);
		}
		if (!(str[lex->sh->i] > ' ' && str[lex->sh->i] <= '~')
			|| str[lex->sh->i] == '>' || str[lex->sh->i] == '<'
			|| str[lex->sh->i] == '|')
		{
			ft_putstr_fd("ERROR PIPE\n", 2);
			return (1);
		}
		lex->sh->i--;
	}
	return (0);
}
