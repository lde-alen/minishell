/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:50 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/04 04:15:03 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_env *lst, t_cmd *cmd_lst)
{
	if (cmd_lst->command[0] == '$')
		ft_expander(lst, cmd_lst);
	if (strcmp(cmd_lst->command, "echo") == 0)
		ft_echo(cmd_lst);
	if (strcmp(cmd_lst->command, "pwd") == 0)
		ft_pwd();
	if (strcmp(cmd_lst->command, "env") == 0)
		print_list_env(lst);
	if (strcmp(cmd_lst->command, "export") == 0)
		ft_export(lst, cmd_lst);
	if (strcmp(cmd_lst->command, "unset") == 0)
		ft_unset(lst, cmd_lst);
	if (strcmp(cmd_lst->command, "cd") == 0)
		ft_cd(cmd_lst);
}
