/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 04:49:15 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/31 07:57:34 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(t_env *lst)
{
	char	**env_path;
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (strcmp(lst->name, "PATH") == 0)
		{
			env_path = ft_split(lst->value, ':');
			return (env_path);
		}
		lst = lst->next;
	}
	return NULL;
}

char	*check_access(t_env *lst, t_cmd *cmd_lst)
{
	char	**env_path;
	char	*post_join;
	char	*path;
	char	*str;
	int		i;

	i = 0;
	env_path = get_path(lst);
	while (env_path[i])
	{
		post_join = ft_strjoin("/", cmd_lst->command);
		str = ft_strjoin(env_path[i], post_join);
		if (access(str, F_OK) == 0)
		{
			path = ft_strdup(str);
			free(str);
			free(post_join);
			return (path);
		}
		free(str);
		free(post_join);
		i++;
	}
	return (NULL);
}

void	main_child(t_env *lst, t_cmd *cmd_lst, char *path)
{
	if (execve(path, cmd_lst->argument, lst_to_char(lst)) < 0)
		perror("Execve problem");
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
