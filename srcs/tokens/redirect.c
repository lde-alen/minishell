/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/05 14:57:40 by asanthos         ###   ########.fr       */
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
	ssize_t	len;

	ft_printf("FLAG_LEN: %d\n", lex->cmd->redir->flag_len);
	len = lex->cmd->redir->flag_len - 1;
	while (len >= 0)
	{
		ft_printf("len: %d\n", len);
		if (lex->cmd->redir->flag[len] != DL_REDIR)
			return (len);
		len--;
	}
	return (0);
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

void	sig(int val)
{
	if (val == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		g_exit = -69;
	}
}

void	free_file(t_redir *redir)
{
	size_t	i;

	i = 0;
	while (i < redir->flag_len)
	{
		free(redir->file[i]);
		redir->file[i] = NULL;
		// if (redir->doc_arr[i])
		// 	free(redir->doc_arr[i]);
		// redir->doc_arr[i] = NULL;
		i++;
	}
	free(redir->file);
	redir->file = NULL;
	free(redir->flag);
	redir->flag = 0;
	if (redir->str || ft_strcmp(redir->str, "") == 0)
		free(redir->str);
}

void	here_doc(t_lex *lex)
{
	char	*store;
	size_t	i;

	// ft_redir_init(lex);
	i = 0;
	lex->cmd->redir->str = ft_strdup("");
	signal(SIGINT, sig);
	while (i < lex->cmd->redir->flag_len)
	{
		store = ft_strdup("");
		if (lex->cmd->redir->flag[i] == DL_REDIR)
		{
			while (ft_strcmp(store, lex->cmd->redir->file[i]) != 0)
			{
				if (g_exit == -69)
				{
					free(store);
					free_file(lex->cmd->redir);
					free_child(lex);
					g_exit = 130;
					exit(130);
				}
				free(store);
				store = readline("> ");
				if (!store)
				{
					free(store);
					free_file(lex->cmd->redir);
					free_child(lex);
					exit(0);
				}
				lex->cmd->redir->str = ft_strjoin(lex->cmd->redir->str, store);
				lex->cmd->redir->str = ft_strjoin(lex->cmd->redir->str, "\n");
			}
		}
		free(store);
		i++;
	}
	fill_doc_arr(lex, lex->cmd->redir->str);
	free(lex->cmd->redir->str);
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
