/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/01 16:17:48 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	find_redir_in(t_lex *lex, size_t type)
{
	int	i;

	i = lex->cmd->redir->flag_len;
	while (i > 0)
	{
		if (lex->cmd->redir->flag[i - 1] == type)
			return (i - 1);
		i--;
	}
	return (-1);
}

size_t	get_last_delimiter(t_lex *lex)
{
	size_t	len;

	len = lex->cmd->redir->flag_len - 1;
	while (lex->cmd->redir->flag[len] != DL_REDIR)
		len--;
	return (len);
}

void	arr_loop(t_lex *lex, char *str_join, char **split_arr, size_t j)
{
	size_t	i;

	i = 0;
	while (i < lex->cmd->redir->flag_len)
	{
		if (lex->cmd->redir->flag[i] == DL_REDIR)
		{
			str_join = ft_strdup("");
			while (split_arr[j] && ft_strcmp(split_arr[j],
					lex->cmd->redir->file[i]) != 0)
			{
				str_join = ft_strjoin(str_join, split_arr[j]);
				str_join = ft_strjoin(str_join, "\n");
				j++;
			}
			j++;
			str_join = ft_strtrim(str_join, "\n");
			lex->cmd->redir->doc_arr[i] = ft_strdup(str_join);
			free(str_join);
		}
		else
			lex->cmd->redir->doc_arr[i] = NULL;
		i++;
	}
	lex->cmd->redir->doc_arr[i] = NULL;
}

void	here_doc(t_lex *lex)
{
	char	*str;
	char	*store;
	size_t	i;

	ft_redir_init(lex);
	i = 0;
	str = ft_strdup("");
	while (i < lex->cmd->redir->flag_len)
	{
		store = ft_strdup("");
		if (lex->cmd->redir->flag[i] == DL_REDIR)
		{
			while (ft_strcmp(store, lex->cmd->redir->file[i]) != 0)
			{
				free(store);
				store = readline("> ");
				str = ft_strjoin(str, store);
				str = ft_strjoin(str, "\n");
			}
		}
		free(store);
		i++;
	}
	fill_doc_arr(lex, str);
	free(str);
}

void	redir(t_lex *lex)
{
	ssize_t	len;
	ssize_t	right;
	ssize_t	left;

	len = lex->cmd->redir->flag_len;
	lex->cmd->redir->left_r = find_redir_in(lex, L_REDIR);
	lex->cmd->redir->left_dr = find_redir_in(lex, DL_REDIR);
	lex->cmd->redir->right_r = find_redir_in(lex, R_REDIR);
	lex->cmd->redir->right_dr = find_redir_in(lex, DR_REDIR);
	left = lex->cmd->redir->left_r - lex->cmd->redir->left_dr;
	right = lex->cmd->redir->right_r - lex->cmd->redir->right_dr;
	fopen_rem(lex, right, left, &len);
	check_redir_type(lex);
	redirect(lex);
}
