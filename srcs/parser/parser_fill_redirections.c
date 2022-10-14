/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:10:14 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/14 13:11:06 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_redir(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == D_QUOTE)
		{
			i++;
			while (str[i] && str[i] != D_QUOTE)
				i++;
			i++;
		}
		else if (str[i] == S_QUOTE)
		{
			i++;
			while (str[i] && str[i] != S_QUOTE)
				i++;
			i++;
		}
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

void	ft_init2_file(t_lex *lex)
{
	size_t	i;

	i = 0;
	while (i < lex->cmd->redir->flag_len)
	{
		lex->cmd->redir->file[i] = (char *)ft_calloc(1, sizeof(char));
		i++;
	}
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

	i = 0;
	j = 0;
	lex->cmd->redir->flag_len = count;
	lex->cmd->redir->flag = (size_t *)malloc(sizeof(size_t) * (count));
	lex->cmd->redir->file = (char **)ft_calloc((count), sizeof(char *));
	ft_init2_file(lex);
	while (lex->cmd->command[i])
	{
		if (lex->cmd->command[i] == D_QUOTE)
		{
			i++;
			while (lex->cmd->command[i] != D_QUOTE)
				i++;
			i++;
		}
		if (lex->cmd->command[i] == S_QUOTE)
		{
			i++;
			while (lex->cmd->command[i] != S_QUOTE)
				i++;
			i++;
		}
		if (lex->cmd->command[i] == '>' || lex->cmd->command[i] == '<')
		{
			i++;
			if (lex->cmd->command[i] == '>')
			{
				lex->cmd->redir->flag[j] = DR_REDIR;
				ft_get_file_name(lex->cmd->command + i, lex, j);
			}
			else if (lex->cmd->command[i] == '<')
			{
				lex->cmd->redir->flag[j] = DL_REDIR;
				ft_get_file_name(lex->cmd->command + i, lex, j);
			}
			else
			{
				i--;
				if (lex->cmd->command[i] == '>')
					lex->cmd->redir->flag[j] = R_REDIR;
				if (lex->cmd->command[i] == '<')
					lex->cmd->redir->flag[j] = L_REDIR;
				ft_get_file_name(lex->cmd->command + i, lex, j);
			}
			j++;
		}
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
