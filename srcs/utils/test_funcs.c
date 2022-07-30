/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 05:23:38 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/30 05:23:52 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**lst_to_char(t_env *lst)
{
	char	**env;
	char	*temp_str;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	temp_str = "";
	env = (char **)malloc(sizeof(char *) * get_lst_len(lst));
	while (lst->next != tmp)
	{
		env[i] = lst->name;
		temp_str = ft_strjoin(env[i], "=");
		env[i] = ft_strjoin(temp_str, lst->value);
		lst = lst->next;
		i++;
		// free(temp_str);
	}
	env[i] = lst->name;
	temp_str = ft_strjoin(env[i], "=");
	env[i] = ft_strjoin(temp_str, lst->value);
	// free(temp_str);
	return (env);
};