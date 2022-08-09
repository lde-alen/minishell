/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:18:14 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/09 09:52:21 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env(char **env)
{
	t_env	*lst;
	char	*env_name;
	char	*env_value;
	char	*div;
	int		i;

	i = 0;
	lst = NULL;
	// lst = (t_env *)malloc(sizeof(t_env));
	while (env[i])
	{
		env_name = ft_substr(env[i], 0, ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '=')));
		div = ft_strchr(env[i], '=');
		env_value = ft_strchr(div, div[1]);
		lst = push_env(lst, env_name, env_value);
		free(env_name);
		i++;
	}
	return (lst);
}
