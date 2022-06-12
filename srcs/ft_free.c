/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:52:17 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/13 03:40:55 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_split(char **split_cmd)
{
	int	i;

	i = 0;
	while (split_cmd[i])
	{
		free(split_cmd[i]);
		i++;
	}
}

void	free_env_lst(t_env *lst)
{
	t_env	*tmp;
	t_env	*store;

	tmp = lst;
	while (lst->next != tmp)
	{
		store = lst->next;
		free(lst);
		lst = store;
	}
	free (lst);
}

void	free_cmd(t_cmd *cmd_lst)
{
	t_cmd	*tmp;
	t_cmd	*store;

	tmp = cmd_lst;
	while (cmd_lst->next != tmp)
	{
		store = cmd_lst->next;
		free(cmd_lst);
		cmd_lst = store;
	}
	free (cmd_lst);
}

void	lst_free(t_cmd *cmd_lst, t_env *lst)
{
	(void)lst;
	free_cmd(cmd_lst);
}
