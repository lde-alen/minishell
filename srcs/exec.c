/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:49:15 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/02 07:00:59 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_child(t_env *lst, t_cmd *cmd_lst, char *path)
{
	if (execve(path, cmd_lst->argument, lst_to_char(lst)) < 0)
		perror("Execve problem");
	// exit(0);
}

void	exec_sys(t_env *lst, t_cmd *cmd_lst)
{
	char	*path;
	int		id;

	id = fork();
	path = check_access(lst, cmd_lst);
	if (path != NULL)
	{
		if (id < 0)
			ft_putendl_fd("Fork failed", 2);
		else if (id == 0)
			main_child(lst, cmd_lst, path);
		waitpid(-1, NULL, 0);
	}
}
