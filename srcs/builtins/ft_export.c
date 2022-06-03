/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:36:39 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/03 15:55:14 by asanthos         ###   ########.fr       */
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
	int	len;
	t_env *tmp;
	char *env_name;

	i = 0;
	tmp = lst;
	while (cmd_lst->argument[i])
	{
		len = ft_strlen(cmd_lst->argument[i]) - ft_strlen(ft_strchr(cmd_lst->argument[i], '='));
		env_name = ft_substr(cmd_lst->argument[i], 0, len);
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
	int		i;
	char	*div;
	t_env	*check;
	
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

// void	lonely_export(t_env *lst)
// {
// 	int		i;
// 	int		j;
// 	t_env	*store;
// 	t_env	*tmp;
// 	t_env	*tmp2;

// 	i = 0;
// 	store = lst;
// 	tmp = lst;
// 	tmp2 = lst->next;
// 	while (lst->next != tmp)
// 	{
// 		j = 0;
// 		while (store->next->next != tmp2)
// 		{
// 			if (lst->name[0])
// 			j++;
// 			store = store->next;
// 		}
// 		i++;
// 		lst = lst->next;
// 	}
// }
