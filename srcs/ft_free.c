/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:52:17 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/05 08:04:48 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_split(char **split_cmd)
{
	int	i;

	i = 0;
	while (split_cmd[i])
	{
		free(split_cmd[i]);
		i++;
	}
}

// void	lst_free(t_cmd *cmd_lst, t_env *lst)
// {
	
// }
