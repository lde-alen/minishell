/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:25:21 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/10 22:56:52 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_arg(t_msh *msh)
{
	size_t	i;

	i = 0;
	get_all_params();
	get_cmd();
}

size_t	ft_count_redir(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			while (str[i] == '>' || str[i] == '<')
				i++;
			i--;
			count++;
		}
		i++;
	}
	return (count);
}

void	ft_fill_r_flags(t_msh *msh, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	msh->cmd->redir->flag_len = count - 1;
	msh->cmd->redir->flag = (size_t *)malloc(sizeof(size_t) * count);
	while (msh->cmd->command[i])
	{
		if (msh->cmd->command[i] == '>' || msh->cmd->command[i] == '<')
		{
			i++;
			if (msh->cmd->command[i] == '>')
				msh->cmd->redir->flag[j] = DR_REDIR;
			else if (msh->cmd->command[i] == '<')
				msh->cmd->redir->flag[j] = DL_REDIR;
			else
			{
				i--;
				if (msh->cmd->command[i] == '>')
					msh->cmd->redir->flag[j] = R_REDIR;
				if (msh->cmd->command[i] == '<')
					msh->cmd->redir->flag[j] = L_REDIR;
			}
		}
		i++;
	}
}

void	ft_init_file(char **file, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		file[i] = (char *)maloc(sizeof(char));
		file[i] = "";
		i++;
	}
	file[i] == NULL;
}

void	ft_fill_r_file(t_msh *msh, size_t count)
{
	size_t	i;

	i = 0;
	msh->cmd->redir->file = (char **)malloc(sizeof(char *) * count);
	ft_init_file(msh->cmd->redir->file, count);
	while (msh->cmd->command[i])
	{
		if (msh->cmd->command[i] == '>' || msh->cmd->command[i] == '<')
		{
			while (msh->cmd->command[i] == '>' || msh->cmd->command[i] == '<')
				i++;
			while (msh->cmd->command[i] == ' ')
				i++;
			while (msh->cmd->command[i] != ' '
				|| msh->cmd->command[i] != '>' || msh->cmd->command[i] != '<'
				|| msh->cmd->command[i])
			{
				
				i++;
			}
		}
		i++;
	}
}

void	ft_fill_redir(t_msh *msh)
{
	size_t	count;

	count = ft_count_redir(msh->cmd->command);
	if (count == 0)
		return ;
	else
	{
		ft_fill_r_flags(msh, count);
		ft_fill_r_file(msh, count);
	}
}

void	ft_fill_command(char **tab, int i, t_msh *msh)
{
	size_t	j;

	while (tab[i])
	{
		j = 0;
		while (tab[i][j] == ' ')
			j++;
		msh->cmd->command = ft_strdup(tab[i] + j);
		msh->cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
		ft_printf("%s\n", msh->cmd->command);
		i++;
	}
}
