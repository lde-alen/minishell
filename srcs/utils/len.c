/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:srcs/parser/parser_init.c
/*   Created: 2022/08/06 18:57:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/03 18:00:16 by lde-alen         ###   ########.fr       */
========
/*   Created: 2022/07/26 07:29:45 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/03 15:06:56 by asanthos         ###   ########.fr       */
>>>>>>>> origin/alka:srcs/utils/len.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init(t_cmd **cmd, t_env **env)
{
<<<<<<<< HEAD:srcs/parser/parser_init.c
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	*env = (t_env *)malloc(sizeof(t_env));
	(*cmd)->command = NULL;
	(*cmd)->next = NULL;
	(*env)->name = NULL;
	(*env)->value = NULL;
	(*env)->prev = *env;
	(*env)->next = *env;
	return (1);
========
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (lst->next != tmp)
	{
		i++;
		lst = lst->next;
	}
	return (i + 1);
}

int	get_args_len(t_cmd *cmd_lst)
{
	int		i;

	i = 0;
	while (cmd_lst->argument[i])
		i++;
	return (i);
>>>>>>>> origin/alka:srcs/utils/len.c
}

int	get_len(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	iter_diff(t_env *lst, t_env *new_node)
{
	int	i;

	i = 0;
	while (lst->name[i] == new_node->name[i])
		i++;
	if (lst->name[i] < new_node->name[i])
		return (1);
	return (0);
}

size_t	get_cmd_len(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
