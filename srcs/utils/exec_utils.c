/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 09:45:55 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/31 10:31:06 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	**lst_to_char(t_env *lst)
{
	char	**env;
	char	*temp_str;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	temp_str = "";
	env = (char **)malloc(sizeof(char *) * (get_lst_len(lst) + 1));
	while (lst->next != tmp)
	{
		env[i] = lst->name;
		temp_str = ft_strjoin(env[i], "=");
		env[i] = ft_strjoin(temp_str, lst->value);
		lst = lst->next;
		i++;
		// free(temp_str);
	}
	env[i] = lst->name;
	temp_str = ft_strjoin(env[i], "=");
	env[i] = ft_strjoin(temp_str, lst->value);
	// free(temp_str);
	return (env);
};
