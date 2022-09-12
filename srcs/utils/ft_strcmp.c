/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:srcs/utils/ft_strcmp.c
/*   Created: 2021/12/07 12:02:16 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/08 16:20:20 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
========
/*   Created: 2022/07/26 07:29:45 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/03 15:06:56 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
>>>>>>>> origin/alka:srcs/utils/len.c

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s2[i]
		&& (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
<<<<<<<< HEAD:srcs/utils/ft_strcmp.c
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
========
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
