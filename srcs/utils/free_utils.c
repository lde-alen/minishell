/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 04:17:35 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/09 14:11:56 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split_res)
{
	int	i;

	i = 0;
	while (split_res[i])
	{
		if (split_res[i])
			free(split_res[i]);
		i++;
	}
	free(split_res);
}

void	free_split_baqala(char **split_res, int i)
{
	while (split_res[i])
	{
		if (split_res[i])
			free(split_res[i]);
		i++;
	}
	free(split_res);
}

void	free_env_kid(char **env_kid)
{
	int	i;

	i = 0;
	while (env_kid[i])
	{
		free(env_kid[i]);
		i++;
	}
	free(env_kid[i]);
	free(env_kid);
}

void	free_file_redir(t_redir *redir)
{
	size_t	i;

	if (redir->file)
	{
		i = 0;
		while (i < redir->flag_len)
		{
			free(redir->file[i]);
			if (redir->doc_arr)
			{
				free(redir->doc_arr[i]);
				redir->doc_arr[i] = NULL;
			}
			i++;
		}
	}
}

void	free_file(t_cmd *tmp, t_redir *redir)
{
	size_t	i;

	i = 0;
	while (i < redir->flag_len)
	{
		free(redir->file[i]);
		redir->file[i] = NULL;
		i++;
	}
	free(redir->file);
	redir->file = NULL;
	free(redir->flag);
	redir->flag = 0;
	if (redir->str || ft_strcmp(redir->str, "") == 0)
		free(redir->str);
	while (tmp)
		free_cmd(&tmp);
}
