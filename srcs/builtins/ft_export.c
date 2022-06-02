/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:36:39 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/01 17:35:57 by asanthos         ###   ########.fr       */
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

void    ft_export(t_env *lst, t_cmd *cmd_lst)
{
	int i;

    i = 0;
	while (cmd_lst->argument[i])
	{
		if (ft_strchr(cmd_lst->argument[i], '=') != NULL)
			div_env(cmd_lst->argument[i], lst);
		i++;
	}
}
