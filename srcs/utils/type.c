/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:07:01 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/18 22:52:26 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ssize_t	check_stat(t_cmd *cmd_lst)
{
	struct stat	path_stat;
	int			stat_ch;

	stat_ch = stat(cmd_lst->argument[0], &path_stat);
	if (stat_ch == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			if (ft_strchr(cmd_lst->argument[0], '/') == 0)
			{
				err_msg("", "command not found");
				g_exit = 127;
			}
			else
			{
				err_msg("", "is a directory");
				g_exit = 126;
			}
			return (g_exit);
		}
	}
	return (0);
}

size_t	check_type(t_cmd *cmd_lst, t_exec **exec)
{
	ssize_t	stat;

	stat = check_stat(cmd_lst);
	if (stat != 0)
		return (stat);
	if ((ft_strchr(cmd_lst->argument[0], '/') == 0 && (*exec)->path == NULL)
		|| (!cmd_lst->argument[0]) || ft_strcmp(cmd_lst->argument[0], "") == 0)
	{
		err_msg("", "command not found");
		g_exit = 127;
		return (g_exit);
	}
	if ((*exec)->path == NULL)
		(*exec)->path = ft_strdup(cmd_lst->command);
	return (0);
}

void	path_check(t_lex *lex, t_exec *exec)
{
	check_path(lex->cmd, &exec);
	if (lex->cmd->command)
	{
		exec->path = check_access(lex->env, lex->cmd);
		set_shlvl(lex, exec);
	}
}
