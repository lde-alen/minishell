/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/07 20:06:28 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	check for errors and invalid synthax:
		*  missing dq
		*  missing sq
		*  invalid after > & <
		*  invalid after >> & <<

*/
int	parser_stage1(char *str, t_sh *sh)
{
	t_bool	ret;

	ret = false;
	sh->i = -1;
	while (str[++(sh->i)] && ret == 0)
	{
		sh->sq = 0;
		sh->dq = 0;
		if (str[sh->i] == '\'')
			ret = check_quotes(str, '\'', sh);
		else if (str[sh->i] == '"')
			ret = check_quotes(str, '"', sh);
		else if (str[sh->i == '>'] || str[sh->i == '>'])
			ret = check_redirections(str, sh);
	}
	return (0);
}

int	ft_parse(char *str, char **src_env)
{
	t_sh	*sh;

	(void)src_env;
	if (!str)
		return (1); 
	sh = (t_sh *)malloc(sizeof(t_sh));
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
