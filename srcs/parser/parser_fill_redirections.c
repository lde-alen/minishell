/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:10:14 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/18 18:15:16 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_redir(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == D_QUOTE)
			quote_loop(str, &i, D_QUOTE);
		else if (str[i] == S_QUOTE)
			quote_loop(str, &i, S_QUOTE);
		else if (str[i] == '>' || str[i] == '<')
		{
			while (str[i] == '>' || str[i] == '<')
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

void	ft_get_file_name(char *str, t_lex *lex, size_t j)
{
	size_t	i;

	i = 1;
	while (str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|')
	{
		ft_append_back(&lex->cmd->redir->file[j], str[i]);
		i++;
	}
}

/**
 * should be working
 */
void	ft_fill_r_flags(t_lex *lex, size_t count)
{
	size_t	i;
	size_t	j;

	ft_fill_r_flags_init(&i, &j, lex, count);
	while (i < ft_strlen(lex->cmd->command))
	{
		if (lex->cmd->command[i] == D_QUOTE)
			cmd_quote_loop(lex, &i, D_QUOTE);
		else if (lex->cmd->command[i] == S_QUOTE)
			cmd_quote_loop(lex, &i, S_QUOTE);
		else if (lex->cmd->command[i] == '>' || lex->cmd->command[i] == '<')
			fill_redir_d_redir_check(&i, &j, lex);
		i++;
	}
}

void	ft_fill_redir(t_lex *lex)
{
	size_t	count;

	count = ft_count_redir(lex->cmd->command);
	if (count == 0)
	{
		lex->cmd->redir = NULL;
		return ;
	}
	else
	{
		lex->cmd->redir = (t_redir *)malloc(sizeof(t_redir));
		lex->cmd->redir->flag_len = 0;
		ft_fill_r_flags(lex, count);
	}
}
