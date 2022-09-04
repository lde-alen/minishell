/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 09:45:55 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/01 15:14:49 by asanthos         ###   ########.fr       */
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
		post_join = ft_strjoin("/", cmd_lst->command);
		str = ft_strjoin(env_path[i], post_join);
		if (access(str, F_OK) == 0)
		{
			path = ft_strdup(str);
			free(str);
			free(post_join);
			free_split(env_path);
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

	if (access(cmd_lst->command, F_OK | X_OK) == 0)
	{
		// if (access(cmd_lst->command, X_OK) == 0)
		// 	return (cmd_lst->command);
		return (cmd_lst->command);
	}
	env_path = get_path(lst);
	path = NULL;
	path = join_path(cmd_lst, path, env_path);
	if (path != NULL)
		return (path);
	free_split(env_path);
	return (NULL);
}

//converts the t_env struct to char **
char	**lst_to_char(t_env **lst)
{
	char	**env;
	char	*temp_str;
	t_env	*tmp;
	size_t	i;

	i = 0;
	tmp = *lst;
	env = (char **)malloc(sizeof(char *) * (get_lst_len(*lst) + 1));
	while (tmp->next != *lst)
	{
		env[i] = ft_strdup(tmp->name);
		temp_str = ft_strjoin(env[i], "=");
		free(env[i]);
		env[i] = ft_strjoin(temp_str, tmp->value);
		free(temp_str);
		tmp = tmp->next;
		i++;
	}
	env[i] = ft_strdup(tmp->name);
	temp_str = ft_strjoin(env[i], "=");
	free(env[i]);
	env[i] = ft_strjoin(temp_str, tmp->value);
	env[i + 1] = NULL;
	free(temp_str);
	return (env);
}
