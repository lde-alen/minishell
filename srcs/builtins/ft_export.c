/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:36:39 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/02 11:45:22 by asanthos         ###   ########.fr       */
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

t_env *check_exist(t_env *lst, t_cmd *cmd_lst)
{
	int i;
    t_env *tmp;

    i = 0;
    tmp = lst;
    while (cmd_lst->argument[i])
    {
        while (lst->next != tmp)
        {
            if (strcmp(cmd_lst->argument[i], lst->name) == 0)
			{
			    printf("here\n");
				return (lst);
			}
            lst = lst->next;
        }
		lst = tmp;
        if (strcmp(cmd_lst->argument[i], lst->name) == 0)
            return (lst);
        i++;
    }
	return (NULL);
}

//can a variable name repeated, data gotta replace existing oneaz
void    ft_export(t_env *lst, t_cmd *cmd_lst)
{
	int i;
	// char *div;
	
    i = 0;
	while (cmd_lst->argument[i])
	{
		if (ft_strchr(cmd_lst->argument[i], '=') != NULL)
		{
			// if (check_exist(lst, cmd_lst) != NULL)
			// {
			// 	printf("boop\n");
			// 	div = ft_strchr(cmd_lst->argument[i], '=');
			// 	lst->value = ft_strchr(div, div[1]);
			// }
			// else
			// {
			    div_env(cmd_lst->argument[i], lst);
			    ft_printf("Lst: %s\n", lst->name);
			    ft_printf("Prev: %s\n", lst->prev->name);
			    ft_printf("Next: %s\n", lst->next->name);
			// }
		}
		i++;
	}
}
