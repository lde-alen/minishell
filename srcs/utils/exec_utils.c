/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 09:45:55 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/08 12:46:49 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//get the available paths from the t_env struct
char	**get_path(t_env *lst)
{
	char	**env_path;
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (ft_strcmp(lst->name, "PATH") == 0)
		{
			env_path = ft_split(lst->value, ':');
			return (env_path);
		}
		lst = lst->next;
	}
	return (NULL);
}

char	*join_path(t_cmd *cmd_lst, char *path, char **env_path)
{
	char	*post_join;
	char	*str;
	size_t	i;

	i = 0;
	while (env_path[i])
	{
		post_join = ft_strjoin(ft_strdup("/"), cmd_lst->command);
		str = ft_strjoin(env_path[i], post_join);
		if (access(str, F_OK) == 0)
		{
			path = ft_strdup(str);
			free(str);
			free(post_join);
			free_split_baqala(env_path, i + 1);
			return (path);
		}
		free(str);
		free(post_join);
		i++;
	}
	return (NULL);
}

//checks existence of command when joined with the path
char	*check_access(t_env *lst, t_cmd *cmd_lst)
{
	char	**env_path;
	char	*path;

	if (access(cmd_lst->command, F_OK | X_OK) == 0
		&& ft_strcmp(cmd_lst->command, "cat") != 0)
	{
		// if (access(cmd_lst->command, X_OK) == 0)
		// 	return (cmd_lst->command);
		return (ft_strdup(cmd_lst->command));
	}
	if (search_env(lst, "PATH") == NULL)
		return (NULL);
	env_path = get_path(lst);
	path = NULL;
	path = join_path(cmd_lst, path, env_path);
	if (path != NULL)
		return (path);
	free(env_path);
	return (NULL);
}

//converts the t_env struct to char **
char	**lst_to_char(t_env **lst)
{
	char	**env;
	t_env	*tmp;
	size_t	i;

	i = 0;
	tmp = *lst;
	env = (char **)malloc(sizeof(char *) * (get_lst_len(*lst) + 1));
	if (!env)
		exit(0);
	while (tmp->next != *lst)
	{
		env[i] = ft_strdup(tmp->name);
		env[i] = ft_strjoin(env[i], "=");
		env[i] = ft_strjoin(env[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	env[i] = ft_strdup(tmp->name);
	env[i] = ft_strjoin(env[i], "=");
	env[i] = ft_strjoin(env[i], tmp->value);
	env[i + 1] = NULL;
	return (env);
}
