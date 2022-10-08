/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:13:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/08 20:42:23 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_env(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp->next != lst)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	if (ft_strcmp(tmp->name, str) == 0)
		return (tmp);
	return (NULL);
}

t_env	*search_oldpwd(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (ft_strcmp(lst->name, "OLDPWD") == 0)
		{
			free(lst->value);
			return (lst);
		}
		lst = lst->next;
	}
	if (ft_strcmp(lst->name, "OLDPWD") == 0)
	{
		free(lst->value);
		return (lst);
	}
	return (NULL);
}

void	change_dir(t_cmd *cmd, t_env *pwd, t_env *store)
{
	char	*buff;

	buff = get_pwd();
	store->value = ft_strdup(pwd->value);
	free(pwd->value);
	if (!cmd->argument[1])
		pwd->value = ft_strdup(buff);
	else
	{
		if (ft_strcmp(cmd->argument[1], "//") == 0)
			pwd->value = ft_strdup("//");
		else
			pwd->value = ft_strdup(buff);
	}
	free(buff);
}

void	cd_dash(t_cmd *cmd, t_env *lst, char **store, char **store_curr)
{
	ssize_t	ret;

	if (!search_env(lst, "OLDPWD")->value)
	{
		err_msg(cmd, "cd", "OLDPWD not set");
		g_exit = 1;
	}
	else
	{
		*store = ft_strdup(search_env(lst, "OLDPWD")->value);
		ret = chdir(*store);
		if (ret < 0)
			exit_stat(errno);
		else
		{
			*store_curr = ft_strdup(search_env(lst, "PWD")->value);
			free(search_env(lst, "PWD")->value);
			free(search_env(lst, "OLDPWD")->value);
			search_env(lst, "PWD")->value = ft_strdup(*store_curr);
			search_env(lst, "OLDPWD")->value = ft_strdup(*store);
			free(*store);
			free(*store_curr);
		}
	}
}

static void	set_check_val(t_cmd *cmd, t_env *lst, int *check, char **env_user)
{
	char	*store;
	char	*store_curr;

	if (!cmd->argument[1] || ft_strcmp(cmd->argument[1], "~") == 0)
	{
		if (search_env(lst, "USER") != NULL)
		{
			*env_user = ft_strjoin(ft_strdup("/Users/"),
					search_env(lst, "USER")->value);
			chdir(*env_user);
		}
	}
	else if (ft_strcmp(cmd->argument[1], "-") == 0)
	{
		if (search_env(lst, "OLDPWD") != NULL)
			cd_dash(cmd, lst, &store, &store_curr);
		else
		{
			err_msg(cmd, "cd", "OLDPWD not set");
			g_exit = 1;
		}
	}
	else
		*check = chdir(cmd->argument[1]);
}

void	ft_cd(t_cmd *cmd, t_env *lst)
{
	t_env	*pwd;
	t_env	*store;
	int		check;
	char	*env_user;

	pwd = search_env(lst, "PWD");
	check = 0;
	set_check_val(cmd, lst, &check, &env_user);
	if (check < 0)
	{
		if (access(cmd->argument[1], F_OK | X_OK) == 0)
			err_msg(cmd, cmd->argument[1], ": Permission denied");
		else
			err_msg(cmd, cmd->argument[1], ": No such file or directory");
		g_exit = 1;
	}
	store = search_oldpwd(lst);
	if (!store)
		return ;
	change_dir(cmd, pwd, store);
}
