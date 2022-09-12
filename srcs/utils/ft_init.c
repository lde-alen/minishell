/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:12:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/12 04:55:29 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_init(t_env *lst)
{
	lst->env_str = NULL;
	lst->name = NULL;
	lst->value = NULL;
	lst->next = NULL;
	lst->prev = NULL;
}
