/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_open.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:43:23 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/10 17:55:51 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fopen_rem(t_lex *lex, ssize_t right, ssize_t left, ssize_t *len)
{
	ssize_t	i;

	i = 0;
	while (i < *len && lex->cmd->redir->flag[*len - 1] == DL_REDIR)
		(*len)--;
	while (i < *len - 1)
	{
		if ((lex->cmd->redir->flag[i] == R_REDIR
				&& (i != find_redir_in(lex, R_REDIR) || !lex->cmd->command))
			|| lex->cmd->redir->flag[i] == DR_REDIR)
		{
			if (((right < -1 && i != lex->cmd->redir->right_r)
					|| (right > -1 && i != lex->cmd->redir->right_dr))
				|| !lex->cmd->command)
				open_file(lex, lex->cmd->redir->file[i], O_TRUNC | O_CREAT);
		}
		else if (lex->cmd->redir->flag[i] == L_REDIR
			&& (i != find_redir_in(lex, L_REDIR) || !lex->cmd->command))
		{
			if ((left < -1 && i != lex->cmd->redir->left_r)
				|| !lex->cmd->command)
				open_file(lex, lex->cmd->redir->file[i], O_TRUNC);
		}
		i++;
	}
}

ssize_t	open_file(t_lex *lex, char *str, int flag)
{
	int		file;

	if (check_perm(lex, str) == -1)
		return (-1);
	file = open(str, flag, 0777);
	if (file < 0)
	{
		access(str, F_OK);
		exit_stat(errno);
		return (-1);
	}
	g_exit = 0;
	return (file);
}

void	fill_doc_arr(t_lex *lex, char *str)
{
	char	**split_arr;
	char	*str_join;
	size_t	j;

	if (str == NULL)
		return ;
	else
	{
		j = 0;
		str_join = NULL;
		lex->cmd->redir->doc_arr = (char **)malloc(sizeof(char *)
				* (lex->cmd->redir->flag_len + 1));
		if (!lex->cmd->redir->doc_arr)
		{
			free_child(lex);
			exit(EXIT_FAILURE);
		}
		split_arr = ft_split(str, '\n');
		arr_loop(lex, str_join, split_arr, j);
		free_split(split_arr);
	}
}
