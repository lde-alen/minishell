/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:46:31 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/18 18:20:24 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_ds_quote(char **tmp, size_t *i, t_lex *lex, int quote)
{
	ft_append_back(tmp, lex->cmd->command[*i]);
	(*i)++;
	while (lex->cmd->command[*i] != quote && lex->cmd->command[*i])
	{
		ft_append_back(tmp, lex->cmd->command[*i]);
		(*i)++;
	}
	if (*i < ft_strlen(lex->cmd->command))
	{
		ft_append_back(tmp, lex->cmd->command[*i]);
		(*i)++;
	}
	if (lex->cmd->command[*i] == ' ')
		ft_append_back(tmp, lex->cmd->command[*i]);
}

void	util_fill_redir(t_lex *lex, size_t *i)
{
	(*i)++;
	if (lex->cmd->command[*i] == '<' || lex->cmd->command[*i] == '>')
		(*i)++;
	while (lex->cmd->command[*i] == ' ')
		(*i)++;
	while ((lex->cmd->command[*i] != ' ' && lex->cmd->command[*i] != '>'
			&& lex->cmd->command[*i] != '<' && lex->cmd->command[*i]))
		(*i)++;
}
