/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:36:39 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/03 11:02:58 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void div_env(char *str, t_env *lst)
{
	char	*env_name;
	char	*env_value;
	char	*div;

	env_name = ft_substr(str, 0, ft_strlen(str) - ft_strlen(ft_strchr(str, '=')));
	div = ft_strchr(str, '=');
	env_value = ft_strchr(div, div[1]);
	lst = push_env(lst, env_name, env_value);
}

t_env	*check_exist(t_env *lst, t_cmd *cmd_lst)
{
	int i;
	t_env *tmp;
	char *env_name;

	i = 0;
	tmp = lst;
	while (cmd_lst->argument[i])
	{
		env_name = ft_substr(cmd_lst->argument[i], 0, ft_strlen(cmd_lst->argument[i]) - ft_strlen(ft_strchr(cmd_lst->argument[i], '=')));
		while (lst->next != tmp)
		{
			if (strcmp(env_name, lst->name) == 0)
				return (lst);
			lst = lst->next;
		}
		if (strcmp(env_name, lst->name) == 0)
			return (lst);
		lst = tmp;
		i++;
	}
	return (NULL);
}

void	ft_export(t_env *lst, t_cmd *cmd_lst)
{
	int i;
	char *div;
	t_env *check;
	
	i = 0;
	while (cmd_lst->argument[i])
	{
		if (ft_strchr(cmd_lst->argument[i], '=') != NULL)
		{
			check = check_exist(lst, cmd_lst);
			if (check != NULL)
			{
				div = ft_strchr(cmd_lst->argument[i], '=');
				check->value = ft_strchr(div, div[1]);
			}
			else
				div_env(cmd_lst->argument[i], lst);
		}
		i++;
	}
}
