/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 09:45:55 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/17 13:42:23 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//get the available paths from the t_env struct
char	**get_path(t_env *lst)
{
	char	**env_path;

	env_path = ft_split(search_env(lst, "PATH")->value, ':');
	if (env_path)
		return (env_path);
	return (NULL);
}

char	*join_path(t_cmd *cmd_lst, char *path, char **env_path)
{
	char	*post_join;
	char	*str;
	size_t	i;

	i = 0;
	if (!env_path)
	{
		return (NULL);
	}
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

	if (search_env(lst, "PATH") == NULL)
		return (NULL);
	env_path = get_path(lst);
	path = NULL;
	path = join_path(cmd_lst, path, env_path);
	if (path != NULL)
		return (path);
	if (access(cmd_lst->command, F_OK | X_OK) == 0
		&& ft_strcmp(cmd_lst->command, "cat") != 0)
		return (ft_strdup(cmd_lst->command));
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
		return (NULL);
	while (tmp != *lst)
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

void	set_path(t_lex *lex, t_exec *exec)
{
	if (lex->cmd->argument)
	{
		if (lex->cmd->argument[0])
			exec->path = check_access(lex->env, lex->cmd);
		else
			exec->path = NULL;
	}
	else
		exec->path = NULL;
}
