/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/04 11:21:15 by lde-alen         ###   ########.fr       */
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

int	ft_fill_arg(char ***argument, char *str)
{
	if (!argument)
		return (-1);
	*argument = ft_split(str, ' ');
	return (1);
}

int	ft_fill_cmd(char **command, char **argument)
{
	if (!argument[0])
		return (-1);
	*command = argument[0];
	return (1);
}

int	ft_init_fptr((**fptr)(t_cmd *cmd))
{
	fptr[0] = &ft_sc;
	fptr[1] = &ft_dc;
	fptr[6] = &ft_bling;
	fptr[2] = &ft_lsr;
	fptr[3] = &ft_rsr;
	fptr[4] = &ft_ldr;
	fptr[5] = &ft_rdr;
	fptr[7] = &ft_p;
}

int	ft_ptr_to_swag(t_cmd *cmd)
{
	int		(*fptr[8])(t_cmd *cmd);
	char	*flag[8];

	ft_init_fptr(fptr);
	fptr[find_index(flag)](cmd);
	return (1);
}

int	ft_parse(char *str, char **src_env)
{
	t_cmd	*cmd;
	t_env	*env;

	(void)src_env;
	(void)str;
	ft_init(&cmd, &env);
	ft_fill_arg(&cmd->argument, str);
	ft_fill_cmd(&cmd->command, &cmd->argument[0]);
	ft_ptr_to_swag(cmd);
	ft_printf("Original str:\n%s\n", str);
	ft_printf("User input is:\n");
	ft_print_char_arr(cmd->argument);
	ft_printf("Command is:\n");
	ft_printf(("%s\n"), cmd->command);
	return (1);
}
