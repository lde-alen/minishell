/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:50 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/18 16:15:22 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//uncomment pipes & redirects when testing builtins
void	exec_cmd(t_env *lst, t_cmd *cmd_lst)
{
	// if (cmd_lst->argument[1][0] == '|')
	// {
	// 	exec_pipe(lst, cmd_lst);
	// 	// exec_pipe(lst, cmd_lst);
	// }
	// else if (ft_strcmp(cmd_lst->argument[1], "<") == 0)
	// 	redirect_in(lst, cmd_lst);
	// else if (ft_strcmp(cmd_lst->argument[1], "<<") == 0)
	// 	here_doc(lst, cmd_lst);
	// else if (ft_strcmp(cmd_lst->argument[1], ">") == 0)
	// 	redirect_out(lst, cmd_lst);
	// else if (ft_strcmp(cmd_lst->argument[1], ">>") == 0)
	// 	append_out(lst, cmd_lst);
	if (cmd_lst->command[0] == '$')
		ft_expander(lst, cmd_lst->command);
	else if (ft_strcmp(cmd_lst->command, "echo") == 0)
		ft_echo(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "pwd") == 0)
		ft_pwd(lst);
	else if (ft_strcmp(cmd_lst->command, "env") == 0)
		print_list_env(lst);
	else if (ft_strcmp(cmd_lst->command, "export") == 0 && cmd_lst->argument[1] != NULL)
		ft_export(lst, cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "export") == 0)
		lonely_export(lst);
	else if (ft_strcmp(cmd_lst->command, "unset") == 0)
		ft_unset(lst, cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "cd") == 0)
		ft_cd(cmd_lst, lst);
	else if (ft_strncmp(cmd_lst->command, "exit", 4) == 0)
		exit(0);
	else
		exec_sys(lst, cmd_lst);
}
