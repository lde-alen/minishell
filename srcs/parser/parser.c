/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/08 20:09:14 by lde-alen         ###   ########.fr       */
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
/*
	Identify quotes or not quotes, expand or not expand 
	and then store accordingly
*/
int	parser_stage2(char *str, t_sh *sh, t_env *env)
{
	ft_printf("euro = %d\n", sh->euro);
	if (sh->euro > 0)
		ft_check_expand(str, sh, env);
	return (0);
}

int	parser_stage1(char *str, t_sh *sh)
{
	t_bool	ret;

	ret = false;
	sh->i = 0;
	sh->euro = 0;
	while (str[sh->i] && ret == false)
	{
		sh->sq = 0;
		sh->dq = 0;
		if (str[sh->i] == '$')
		{
			ft_printf("WTF");
			sh->euro += 1;
		}
		if (str[sh->i] == '\'')
			ret = check_quotes(str, '\'', sh);
		else if (str[sh->i] == '"')
			ret = check_quotes(str, '"', sh);
		else if (str[sh->i == '>'] || str[sh->i == '>'])
			ret = check_redirections(str, sh);
		sh->i++;
	}
	if (ret == false)
		return (0);
	else
		return (1);
}

int	ft_parse(char *str, t_env *env)
{
	t_sh	*sh;

	if (!str)
		return (1);
	sh = (t_sh *)malloc(sizeof(t_sh));
	ft_printf("return of stage1 = %d\n", parser_stage1(str, sh));
	if (parser_stage1(str, sh) == 0)
		parser_stage2(str, sh, env);
	free (sh);
	return (1);
}
	// ft_printf("%d\n", check_sq(str));
	// ft_init(&cmd, &env);
	// ft_fill_arg(&cmd->argument, str);
	// ft_fill_cmd(&cmd->command, &cmd->argument[0]);
	// ft_printf("Original str:\n%s\n", str);
	// ft_printf("User input is:\n");
	// ft_print_char_arr(cmd->argument);
	// ft_printf("Command is:\n");
	// ft_printf(("%s\n"), cmd->command);
