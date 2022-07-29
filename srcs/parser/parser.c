/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/29 20:04:38 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_init(t_cmd **cmd, t_env **env)
{
	*cmd = (t_cmd *)malloc(sizeof(cmd));
	*env = (t_env *)malloc(sizeof(env));
	(*cmd)->command = NULL;
	(*cmd)->token = -1;
	(*cmd)->side = 0;
	(*cmd)->next = NULL;
	(*env)->name = NULL;
	(*env)->value = NULL;
	(*env)->prev = *env;
	(*env)->next = *env;
	return (1);
}

int	ft_fill_arg(char **argument, char *str)
{
	argument = ft_split(str, ' ');
	return (1);
}

int	ft_parse(char *str, char **src_env)
{
	t_cmd	*cmd;
	t_env	*env;

	(void)src_env;
	(void)str;
	ft_init(&cmd, &env);
	ft_fill_arg(cmd->argument, str);
	ft_printf("Original str:\n%s\n", str);
	ft_printf("User input is:\n");
	ft_print_char_arr(cmd->argument);
	return (1);
}

