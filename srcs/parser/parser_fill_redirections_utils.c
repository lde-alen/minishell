/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_redirections_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:15:56 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/17 18:04:52 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_r_flags_init(size_t *i, size_t *j, t_lex *lex, size_t count)
{
	size_t	k;

	k = 0;
	*i = 0;
	*j = 0;
	lex->cmd->redir->flag_len = count;
	lex->cmd->redir->flag = (size_t *)malloc(sizeof(size_t) * (count));
	lex->cmd->redir->file = (char **)ft_calloc((count + 1), sizeof(char *));
	while (k < lex->cmd->redir->flag_len)
	{
		lex->cmd->redir->file[k] = (char *)ft_calloc(1, sizeof(char));
		k++;
	}
}

void	quote_loop(char *str, size_t *i, int quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	(*i)++;
}

void	cmd_quote_loop(t_lex *lex, size_t *i, int quote)
{
	(*i)++;
	while (lex->cmd->command[*i] != quote && lex->cmd->command[*i])
		(*i)++;
	(*i)++;
}

void	fill_redir_d_redir_check(size_t *i, size_t *j, t_lex *lex)
{
	(*i)++;
	if (lex->cmd->command[*i] == '>')
	{
		lex->cmd->redir->flag[*j] = DR_REDIR;
		ft_get_file_name(lex->cmd->command + *i, lex, *j);
	}
	else if (lex->cmd->command[*i] == '<')
	{
		lex->cmd->redir->flag[*j] = DL_REDIR;
		ft_get_file_name(lex->cmd->command + *i, lex, *j);
	}
	else
	{
		(*i)--;
		if (lex->cmd->command[*i] == '>')
			lex->cmd->redir->flag[*j] = R_REDIR;
		if (lex->cmd->command[*i] == '<')
			lex->cmd->redir->flag[*j] = L_REDIR;
		ft_get_file_name(lex->cmd->command + *i, lex, *j);
	}
	(*j)++;
}
