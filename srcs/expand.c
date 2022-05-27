/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:48:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/05/27 20:58:25 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_expander(char *str, char *env[])
{
	int		i;
	char	*div;
	char	*sub;

	i = 0;
	while (env[i])
	{
		sub = ft_substr(env[i], 0, ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '=')));
		if (strcmp(sub, ft_strchr(str, str[1])) == 0)
		{
			div = ft_strchr(env[i], '=');
			ft_putendl_fd(ft_strchr(div, div[1]), 1);
			break ;
		}
		i++;
	}
}
