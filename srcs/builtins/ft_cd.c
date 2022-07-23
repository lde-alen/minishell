/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 04:13:06 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/24 03:15:45 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env   *search_pwd(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (strcmp(lst->name, "PWD") == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_env   *search_oldpwd(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (strcmp(lst->name, "OLDPWD") == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void ft_cd(t_cmd *cmd_lst, t_env *lst)
{
	char	*buff;
	t_env	*pwd;

	pwd = search_pwd(lst);
	chdir(cmd_lst->argument[0]);
	buff = get_pwd();
	search_oldpwd(lst)->value = pwd->value;
	if (strcmp(cmd_lst->argument[0], "//") == 0)
		pwd->value = "//";
	else
		pwd->value = buff;
	// free(buff);
}
