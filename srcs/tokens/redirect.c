/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/01 11:34:02 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(t_lex *lex, char *file)
{
	lex->cmd->redir->flag_in = O_RDONLY;
	lex->cmd->redir->file_in = file;
}

void	redirect_out(t_lex *lex, char *file)
{
	lex->cmd->redir->flag_out = O_TRUNC | O_CREAT | O_WRONLY;
	lex->cmd->redir->file_out = file;
}

void	append_out(t_lex *lex, char *file)
{
	lex->cmd->redir->flag_out = O_APPEND | O_WRONLY | O_CREAT;
	lex->cmd->redir->file_out = file;
}

void	check_redir_type(t_lex *lex)
{
	if (lex->cmd->redir->left_r > lex->cmd->redir->left_dr)
		redirect_in(lex,
			ft_strdup(lex->cmd->redir->file[lex->cmd->redir->left_r]));
	else if (lex->cmd->redir->left_dr > lex->cmd->redir->left_r)
	{
		dup_doc(lex);
		lex->cmd->redir->file_in = NULL;
		lex->cmd->redir->flag_in = -1;
	}
	else
		redirect_in(lex, NULL);
	if (lex->cmd->redir->right_r > lex->cmd->redir->right_dr)
		redirect_out(lex,
			ft_strdup(lex->cmd->redir->file[lex->cmd->redir->right_r]));
	else if (lex->cmd->redir->right_dr > lex->cmd->redir->right_r)
		append_out(lex,
			ft_strdup(lex->cmd->redir->file[lex->cmd->redir->right_dr]));
	else
		redirect_out(lex, NULL);
}

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
		split_arr = ft_split(str, '\n');
		arr_loop(lex, str_join, split_arr, j);
		free_split(split_arr);
	}
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
