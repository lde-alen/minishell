/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/27 12:56:49 by asanthos         ###   ########.fr       */
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

size_t	get_last_delimiter(t_lex *lex)
{
	size_t	len;

	len = lex->cmd->redir->flag_len - 1;
	while (lex->cmd->redir->flag[len] != DL_REDIR)
		len--;
	return (len);
}

void	check_redir_type(t_lex *lex, t_exec *exec)
{
	if (lex->cmd->redir->left_r > lex->cmd->redir->left_dr)
		redirect_in(lex, lex->cmd->redir->file[lex->cmd->redir->left_r]);
	else if (lex->cmd->redir->left_dr > lex->cmd->redir->left_r)
		redirect_in(lex, lex->cmd->redir->doc_arr[lex->cmd->redir->left_dr]);
	else
		redirect_in(lex, NULL);
	if (lex->cmd->redir->right_r > lex->cmd->redir->right_dr)
		redirect_out(lex, lex->cmd->redir->file[lex->cmd->redir->right_r]);
	else if (lex->cmd->redir->right_dr > lex->cmd->redir->right_r)
		append_out(lex, lex->cmd->redir->file[lex->cmd->redir->right_dr]);
	else
		redirect_out(lex, NULL);
	redirect(lex, exec);
}

ssize_t	find_redir_in(t_lex *lex, size_t type)
{
	int	i;

	i = lex->cmd->redir->flag_len;
	while (i >= 0)
	{
		if (lex->cmd->redir->flag[i - 1] == type)
			return (i - 1);
		i--;
	}
	return (-1);
}

size_t	count_redir(t_lex *lex)
{
	size_t	i;
	size_t	checker;

	checker = 0;
	i = 0;
	while (i < lex->cmd->redir->flag_len)
	{
		if (lex->cmd->redir->flag[i] == DL_REDIR)
			checker++;
		i++;
	}
	return (checker);
}

void	fill_doc_arr(t_lex *lex, char *str)
{
	char	**split_arr;
	char	*str_join;
	size_t	i;
	int		j;

	if (str == NULL)
		return ;
	else
	{
		i = 0;
		j = 0;
		str_join = ft_strdup("");
		lex->cmd->redir->doc_arr = (char **)malloc(sizeof(char *) * lex->cmd->redir->flag_len);
		split_arr = ft_split(str, '\n');
		while (i < lex->cmd->redir->flag_len)
		{
			if (lex->cmd->redir->flag[i] == DL_REDIR)
			{
				while (split_arr[j] && split_arr[j] != lex->cmd->redir->file[i])
				{
					str_join = ft_strjoin(str_join, split_arr[j]);
					str_join = ft_strjoin(str_join, "\n");
					j++;
				}
				lex->cmd->redir->doc_arr[i] = ft_strdup(str);
			}
			else
				lex->cmd->redir->doc_arr[i] = NULL;
			i++;
		}
		lex->cmd->redir->doc_arr[i] = NULL;
	}
}

void	here_doc(t_lex *lex, t_exec *exec)
{
	int		file;
	char	*file_name;
	char	*str;
	char	*store;
	size_t	i;

	(void)exec;
	file_name = lex->cmd->redir->file[find_redir_in(lex, DL_REDIR)];
	file = open(file_name, O_CREAT | O_RDWR, 0777);
	i = 0;
	str = ft_strdup("");
	store = ft_strdup("");
	while (i < lex->cmd->redir->flag_len)
	{
		if (lex->cmd->redir->flag[i] == DL_REDIR)
		{
			while (ft_strcmp(store, lex->cmd->redir->file[i]) != 0)
			{
				store = readline("> ");
				str = ft_strjoin(str, store);
				str = ft_strjoin(str, "\n");
				if (get_last_delimiter(lex) == i
					&& ft_strcmp(str, lex->cmd->redir->file[i]) != 0)
					ft_putendl_fd(str, file);
			}
		}
		i++;
	}
	ft_printf("HERE: %s\n", str);
	fill_doc_arr(lex, str);
	close(file);
}
