/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/13 23:30:35 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	start filling struct,
	trim spaces if not inside quotes
	trim initial '' and ""
*/
// int	parser_stage2(char *str, t_sh *sh, t_env *env)
// {
// 	char	*name;

// 	sh->i = 0;
// 	sh->euro = 0;
// 	while (str[sh->i] && ret == false)
// 	{
// 		sh->sq = 0;
// 		sh->dq = 0;
// 		if (str[sh->i] == '\'')
// 			check_fill_quotes(str, '\'', sh, env);
// 		else if (str[sh->i] == '"')
// 			check_fill_quotes(str, '"', sh, env);
// 		else if (str[sh->i == '>'] || str[sh->i == '>'])
// 			check_fill_redirections(str, sh);
// 		if (str[sh->i] == '$')
// 		{
// 			name = ft_calloc(2, sizeof(char));
// 			name[0] = '$';
// 			sh->i++;
// 			if ((ft_isdigit(str[sh->i]) == 1)
// 				&& str[sh->i - 1] == '$')
// 				sh->i++;
// 			else
// 			{
// 				while (str[sh->i] && str[sh->i] != '$'
// 					&& ft_isalnum(str[sh->i]) == 1)
// 				{
// 					name = ft_append_char(name, str[sh->i]);
// 					sh->i++;
// 				}
// 				ft_expand(env, name);
// 				sh->i--;
// 			}
// 			free(name);
// 		}
// 		sh->i++;
// 	}
// }

int	parser_stage1(char *str, t_sh *sh)
{
	t_bool	ret;

	ret = false;
	sh->i = 0;
	while (str[sh->i] && ret == false)
	{
		sh->sq = 0;
		sh->dq = 0;
		if (str[sh->i] == '\'')
			ret = check_quotes(str, '\'', sh);
		else if (str[sh->i] == '"')
			ret = check_quotes(str, '"', sh);
		else if (str[sh->i == '>'] || str[sh->i == '<'])
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
	(void)env;
	sh = (t_sh *)malloc(sizeof(t_sh));
	if (parser_stage1(str, sh) == 0)
		ft_printf("\nhayeh\n");
		// parser_stage2(str, sh, env);
	free (sh);
	return (1);
}
