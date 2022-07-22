/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:50 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/13 02:31:18 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_env *lst, t_cmd *cmd_lst)
{
	if (cmd_lst->command[0] == '$')
		ft_expander(lst, cmd_lst->command, 0);
	if (strcmp(cmd_lst->command, "echo") == 0)
		ft_echo(cmd_lst, lst);
	if (strcmp(cmd_lst->command, "pwd") == 0)
		ft_pwd(lst);
	if (strcmp(cmd_lst->command, "env") == 0)
		print_list_env(lst);
	if (strcmp(cmd_lst->command, "export") == 0 && cmd_lst->argument[0] != NULL)
		ft_export(lst, cmd_lst);
	else if (strcmp(cmd_lst->command, "export") == 0)
		lonely_export(lst);
	if (strcmp(cmd_lst->command, "unset") == 0)
		ft_unset(lst, cmd_lst);
	if (strcmp(cmd_lst->command, "cd") == 0)
		ft_cd(cmd_lst, lst);
	if (ft_strncmp(cmd_lst->command, "exit", 4) == 0)
		exit(0);
}
