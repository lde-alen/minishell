/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 04:17:35 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/09 04:18:12 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split_res)
{
	int	i;

	i = 0;
	while (split_res[i])
	{
		if (split_res[i])
			free(split_res[i]);
		i++;
	}
	free(split_res);
}

void	free_split_baqala(char **split_res, int i)
{
	while (split_res[i])
	{
		if (split_res[i])
			free(split_res[i]);
		i++;
	}
	free(split_res);
}

void	free_env_kid(char **env_kid)
{
	int	i;

	i = 0;
	while (env_kid[i])
	{
		free(env_kid[i]);
		i++;
	}
	free(env_kid[i]);
	free(env_kid);
}
