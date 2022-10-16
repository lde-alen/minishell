/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:22:22 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/16 14:49:06 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_d_quote_check(t_lex *lex, char *str, size_t *i)
{
	lex->sh->dq = 1;
	(*i)++;
	while (str[*i] != '"' && str[*i])
	{
		if (str[*i] == '$')
			ft_check_expand(str, lex);
		(*i)++;
	}
}

void	redir_s_quote_check(t_lex *lex, char *str, size_t *i)
{
	lex->sh->sq = 1;
	(*i)++;
	while (str[*i] != '\'' && str[*i])
		(*i)++;
}

int	redir_r_redir(t_lex *lex, char *str, size_t *i)
{
	lex->sh->sr = 1;
	while (str[*i] == '>' && str[*i])
	{
		lex->sh->sr++;
		(*i)++;
	}
	if (lex->sh->sr > 2)
	{
		ft_putstr_fd("ERROR REDIR\n", 2);
		return (1);
	}
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	if (!(str[*i] > ' ' && str[*i] <= '~')
		|| str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
	{
		ft_putstr_fd("ERROR REDIR\n", 2);
		return (1);
	}
	if (str[*i] == '$')
		ft_check_expand(str, lex);
	return (0);
}

int	redir_l_redir(t_lex *lex, char *str, size_t *i)
{
	(*i)++;
	lex->sh->sr = 1;
	while (str[*i] == '<' && str[*i])
	{
		lex->sh->sr++;
		(*i)++;
	}
	if (lex->sh->sr > 2)
	{
		ft_putstr_fd("ERROR REDIR\n", 2);
		return (1);
	}
	while (str[*i] == ' ' && str[*i])
		(*i)++;
	if (!(str[*i] > ' ' && str[*i] <= '~')
		|| str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
	{
		ft_putstr_fd("ERROR REDIR\n", 2);
		return (1);
	}
	if (str[*i] == '$')
		ft_check_expand(str, lex);
	(*i)--;
	return (0);
}
