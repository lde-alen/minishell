/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:10:14 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/11 04:49:49 by lde-alen         ###   ########.fr       */
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

/**
 * should be working
 */
void	ft_fill_r_flags(t_msh *msh, size_t count)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	j = 0;
	x = 0;
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
			j++;
		}
		i++;
	}
}

// void	ft_fill_r_file(t_msh *msh, size_t count)
// {
// 	size_t	i;

// 	i = 0;

// }
void	ft_fill_redir(t_msh *msh)
{
	size_t	count;

	count = ft_count_redir(msh->cmd->command);
	if (count == 0)
		return ;
	else
	{
		msh->cmd->redir = (t_redir *)malloc(sizeof(t_redir));
		ft_fill_r_flags(msh, count);
		// ft_fill_r_file(msh, count);
	}
}
