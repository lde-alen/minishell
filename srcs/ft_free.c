/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:52:17 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/07 21:14:04 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split_res)
{
	int	i;

	i = 0;
	while (split_res[i])
	{
		free(split_res[i]);
		i++;
	}
	free(split_res);
}

void	free_env_lst(t_env *lst)
{
	t_env	*tmp;
	t_env	*store;

	tmp = lst;
	while (lst->next != tmp)
	{
		store = lst->next;
		free(lst->name);
		if (lst->export_flag == 1)
			free(lst->value);
		free(lst);
		lst = store;
	}
	free(lst->name);
	if (lst->export_flag == 1)
		free(lst->value);
	free (lst);
}

void	free_cmd(t_cmd *cmd_lst)
{
	int	i;

	i = 0;
	while (cmd_lst->argument[i])
	{
		free(cmd_lst->argument[i]);
		i++;
	}
	free(cmd_lst->argument);
	free(cmd_lst);
}
