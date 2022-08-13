/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:18:14 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/13 18:00:57 by lde-alen         ###   ########.fr       */
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
	while (env[i])
	{
		env_name = ft_substr(env[i], 0,
				ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '=')));
		div = ft_strchr(env[i], '=');
		env_value = ft_strchr(div, div[1]);
		lst = push_env(lst, env_name, env_value);
		free(env_name);
		i++;
	}
	return (lst);
}
