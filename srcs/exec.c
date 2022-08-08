/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:49:15 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/08 16:39:08 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	main_child2(t_env *lst, t_cmd *cmd_lst, char *path, char **env_kid)
{
	(void)lst;
	if (execve(path, cmd_lst->argument, env_kid) < 0)
		perror("Execve problem");
	// exit(0);
}

void	exec_sys(t_env *lst, t_cmd *cmd_lst)
{
	char	**env_kid;
	char	*path;
	int		id;

	id = fork();
	env_kid = lst_to_char(lst);
	path = check_access(lst, cmd_lst);
	if (path != NULL)
	{
		if (id < 0)
			ft_putendl_fd("Fork failed", 2);
		else if (id == 0)
			main_child2(lst, cmd_lst, path, env_kid);
		waitpid(-1, NULL, 0);
	}
	free(path);
	free_env_kid(env_kid);
}
