/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 09:45:55 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/25 18:02:55 by asanthos         ###   ########.fr       */
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

//checks existence of command when joined with the path
char	*check_access(t_env *lst, t_cmd *cmd_lst)
{
	char	**env_path;
	char	*post_join;
	char	*path;
	char	*str;
	int		i;

	if (access(cmd_lst->command, F_OK) == 0)
		return (cmd_lst->command);
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
			free_split(env_path);
			return (path);
		}
		free(str);
		free(post_join);
		i++;
	}
	free_split(env_path);
	return (NULL);
}

//converts the t_env struct to char **
char	**lst_to_char(t_env *lst)
{
	char	**env;
	char	*temp_str;
	t_env	*tmp;
	size_t	i;

	i = 0;
	tmp = lst;
	temp_str = "";
	env = (char **)malloc(sizeof(char *) * (get_lst_len(lst) + 1));
	while (lst->next != tmp)
	{
		env[i] = ft_strdup(lst->name);
		temp_str = ft_strjoin(env[i], "=");
		free(env[i]);
		env[i] = ft_strjoin(temp_str, lst->value);
		free(temp_str);
		lst = lst->next;
		i++;
	}
	env[i] = ft_strdup(lst->name);
	temp_str = ft_strjoin(env[i], "=");
	free(env[i]);
	env[i] = ft_strjoin(temp_str, lst->value);
	env[i + 1] = NULL;
	free(temp_str);
	return (env);
}
