/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:45:21 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/01 02:10:49 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_echo	*filter_list(t_echo *lst)
{
	int		i;

	i = 2;
	lst = lst->next;
	while (lst != NULL)
	{
		if (ft_strlen(lst->args) > 1 && lst->args[0] == '-'
			&& lst->args[1] == 'n')
		{
			if (ft_strlen(lst->args) > 2)
			{
				if (lst->args[2] == 'n')
				{
					while (lst->args[i] == 'n')
					{
						if (lst->args[i + 1] != 'n' && lst->args[i + 1] != '\0')
							return (lst);
						i++;
					}
				}
				else
					return (lst);
			}
		}
		else
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	push(t_echo *lst, char *new_data)
{
	t_echo	*new_node;
	t_echo	*temp_node;

	if (!lst)
		return ;
	temp_node = lst;
	new_node = (t_echo *)malloc(sizeof(t_echo));
	new_node->args = new_data;
	while (lst->next != NULL)
		lst = lst->next;
	lst->next = new_node;
	new_node->next = NULL;
	lst = temp_node;
}

char	*join_nodes(t_echo *head, t_echo *ret_node)
{
	char	*str;

	str = "";
	while (head != NULL)
	{
		if (head == ret_node)
		{
			while (head != NULL)
			{
				str = (char *)malloc(sizeof(char) * ft_strlen(head->args));
				str = ft_strjoin(str, " ");
				str = ft_strjoin(str, head->args);
				str = ft_strjoin(str, " ");
				head = head->next;
			}
			return (str);
		}
		head = head->next;
	}
	return (str);
}

void	print_list(t_echo *head, t_echo *ret_node)
{
	while (head != NULL)
	{
		if (head == ret_node)
		{
			while (head != NULL)
			{
				printf("%s\n", head->args);
				head = head->next;
			}
			return ;
		}
		head = head->next;
	}
}

void	ft_echo(char *str)
{
	t_echo	*e_nodes;
	t_echo	*ret_node;
	char	**split_res;
	int		i;

	i = 0;
	split_res = ft_split(str, ' ');
	e_nodes = (t_echo *)malloc(sizeof(t_echo));
	e_nodes->args = split_res[i++];
	e_nodes->next = NULL;
	while (split_res[i])
	{
		push(e_nodes, split_res[i]);
		i++;
	}
	if (i == 1)
	{
		ft_putendl_fd("", 1);
		return ;
	}
	ret_node = filter_list(e_nodes);
	ft_putendl_fd(join_nodes(e_nodes, ret_node), 1);
	// print_list(e_nodes, ret_node);
}
