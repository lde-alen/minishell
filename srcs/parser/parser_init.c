/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:57:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/15 15:15:05 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init(t_cmd **cmd, t_env **env)
{
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	*env = (t_env *)malloc(sizeof(t_env));
	(*cmd)->argument = NULL;
	(*cmd)->command = NULL;
	(*cmd)->next = NULL;
	(*env)->name = NULL;
	(*env)->value = NULL;
	(*env)->prev = *env;
	(*env)->next = *env;
	return (1);
}
