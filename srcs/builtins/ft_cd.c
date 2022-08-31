/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:13:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/31 11:55:34 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_pwd(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp->next != lst)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
			return (tmp);
		tmp = tmp->next;
	}
	if (ft_strcmp(tmp->name, "PWD") == 0)
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

void	ft_cd(t_cmd *cmd, t_env *lst)
{
	t_env	*pwd;
	t_env	*store;
	int		check;

	pwd = search_pwd(lst);
	check = 0;
	if (!cmd->argument[1])
	{
		chdir("/Desktop");
		chdir("../");
	}
	else
		check = chdir(cmd->argument[1]);
	if (check < 0)
	{
		if (access(cmd->argument[1], F_OK) == 0)
			err_msg(cmd, cmd->argument[1], "': Not a directory");
		else
			err_msg(cmd, cmd->argument[1], "': No such file or directory");
		g_exit = 1;
	}
	store = search_oldpwd(lst);
	if (!store)
		return ;
	change_dir(cmd, pwd, store);
}
