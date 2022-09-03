/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:57:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/03 18:00:16 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init(t_cmd **cmd, t_env **env)
{
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	*env = (t_env *)malloc(sizeof(t_env));
	(*cmd)->command = NULL;
	(*cmd)->next = NULL;
	(*env)->name = NULL;
	(*env)->value = NULL;
	(*env)->prev = *env;
	(*env)->next = *env;
	return (1);
}
