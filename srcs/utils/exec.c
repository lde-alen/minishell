/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:25:51 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/25 15:45:58 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	exec_builtin(t_env *lst, t_cmd *cmd_lst)
{
	if (cmd_lst->command[0] == '$')
		ft_expander(lst, cmd_lst->command);
	else if (ft_strcmp(cmd_lst->command, "echo") == 0)
		ft_echo(cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "pwd") == 0)
		ft_pwd(lst);
	else if (ft_strcmp(cmd_lst->command, "env") == 0)
		print_list_env(lst);
	else if (ft_strcmp(cmd_lst->command, "export") == 0
		&& cmd_lst->argument[1] != NULL)
		ft_export(lst, cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "export") == 0)
		lonely_export(lst);
	else if (ft_strcmp(cmd_lst->command, "unset") == 0)
		ft_unset(lst, cmd_lst);
	else if (ft_strcmp(cmd_lst->command, "cd") == 0)
		ft_cd(cmd_lst, lst);
	else if (ft_strcmp(cmd_lst->command, "exit") == 0)
		exit(0);
	else
		return (1);
	return (0);
}

void	exec_alone(t_cmd *cmd_lst, t_env *lst, ssize_t *id, char *path)
{
	char	**env_kid;

	if (exec_builtin(lst, cmd_lst) == 0)
	{
		free_cmd(&cmd_lst);
		return ;
	}
	env_kid = lst_to_char(lst);
	id[0] = fork();
	if (id[0] < 0)
		perror("fork");
	else if (id[0] == 0)
		main_child2(cmd_lst, path, env_kid);
	free_env_kid(env_kid);
	free_cmd(&cmd_lst);
}

void	exec_sys(t_env *lst, t_cmd *cmd_lst)
{
	int			**fd;
	ssize_t		*id;
	size_t		i;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * get_cmd_len(cmd_lst));
	id = (ssize_t *)malloc(sizeof(ssize_t) * (get_cmd_len(cmd_lst) + 1));
	while (i < get_cmd_len(cmd_lst))
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	if (check_all_path(lst, cmd_lst) == 1)
		return ;
	fork_arr(lst, cmd_lst, fd, id);
}
