/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/07 18:11:44 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	check for errors and invalid synthax:
		*  missing dq
		*  missing sq
		*  invalid after > & <
		*  invalid after >> & <<

		get flag to see if inside quotes

		for double redirrections check both at the same time, ignore char * for >> and just
		check for > and then check what is after and so one (cf: try in bash anc check bash logic
		+ execution order and error messages)
		if not single check for double
		if double available check for only double >>
		if double not availabe it is only single
		cf: for a double to be available with matching you must have at least 4
		ps check if trim can work for spaces.
*/
int	parser_stage1(char *str, t_sh *sh)
{
	t_bool	ret;

	ret = false;
	sh->i = -1;
	while (str[++(sh->i)] && ret == 0)
	{
		if (str[sh->i] == '\'')
			ret = check_quotes(str, '\'', sh);
		else if (str[sh->i] == '"')
			ret = check_quotes(str, '"', sh);
		ret = check_redirections(str, '>');
	}
	// check_redirections(str, '<');
	return (0);
}

int	ft_parse(char *str, char **src_env)
{
	t_sh	*sh;

	(void)src_env;
	if (!str)
		return (1); 
	sh = (t_sh *)malloc(sizeof(t_sh));
	sh->j = 0;
	parser_stage1(str, sh);
	// parser_stage2;
	// ft_printf("%d\n", check_sq(str));
	// ft_init(&cmd, &env);
	// ft_fill_arg(&cmd->argument, str);
	// ft_fill_cmd(&cmd->command, &cmd->argument[0]);
	// ft_printf("Original str:\n%s\n", str);
	// ft_printf("User input is:\n");
	// ft_print_char_arr(cmd->argument);
	// ft_printf("Command is:\n");
	// ft_printf(("%s\n"), cmd->command);
	return (1);
}
