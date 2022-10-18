/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:13:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/19 01:18:46 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (store)
		store->value = ft_strdup(buff);
	if (pwd && pwd->value)
		free(pwd->value);
	if (buff && pwd)
	{
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
	else
		if (buff)
			free(buff);
}

void	cd_dash(t_env *lst, char **store, char **store_curr)
{
	ssize_t	ret;

	if (!search_env(lst, "OLDPWD")->value)
	{
		err_msg("cd", "OLDPWD not set");
		g_exit = 1;
	}
	else
	{
		*store_curr = ft_strdup(get_pwd());
		*store = ft_strdup(search_env(lst, "OLDPWD")->value);
		free(search_env(lst, "OLDPWD")->value);
		search_env(lst, "OLDPWD")->value = ft_strdup(*store_curr);
		ret = chdir(*store);
		if (ret < 0)
			exit_stat(errno);
		else
		{
			if (search_env(lst, "PWD"))
			{
				free(search_env(lst, "PWD")->value);
				search_env(lst, "PWD")->value = ft_strdup(*store);
			}
		}
		if (*store)
			free(*store);
		if (*store_curr)
			free(*store_curr);
		ft_putendl_fd(search_env(lst, "PWD")->value, 1);
	}
}

static int	set_check_val(t_cmd *cmd, t_env *lst, int *check, char **env_user)
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
			cd_dash(lst, &store, &store_curr);
		else
		{
			err_msg("cd", "OLDPWD not set");
			g_exit = 1;
		}
		return (1);
	}
	else
		*check = chdir(cmd->argument[1]);
	return (1);
}

void	ft_cd(t_cmd *cmd, t_env *lst)
{
	t_env		*pwd;
	t_env		*store;
	int			check;
	char		*env_user;
	struct stat	path_stat;

	g_exit = 0;
	pwd = search_env(lst, "PWD");
	check = 0;
	if (set_check_val(cmd, lst, &check, &env_user) == 1)
		return ;
	if (check < 0)
	{
		if (stat(cmd->argument[1], &path_stat) == 0)
		{
			if (!S_ISDIR(path_stat.st_mode))
				err_msg(cmd->argument[1], ": Not a directory");
			else
				err_msg(cmd->argument[1], ": Permission denied");
		}
		else if (access(cmd->argument[1], F_OK) != 0)
			err_msg(cmd->argument[1], ": No such file or directory");
		g_exit = 1;
		return ;
	}
	store = search_oldpwd(lst);
	if (!store)
		return ;
	change_dir(cmd, pwd, store);
}
