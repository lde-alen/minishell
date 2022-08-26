/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/26 14:52:59 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	start filling struct,
	trim spaces if not inside quotes
	trim initial '' and "" at the end
*/
// int	parser_stage2(char *str, t_msh *msh)
// {
// 	char	*name;

// 	msh->sh->i = 0;
// 	msh->sh->euro = 0;
// 	while (str[msh->sh->i])
// 	{
// 		msh->sh->sq = 0;
// 		msh->sh->dq = 0;
// 		if (str[msh->sh->i] == '\'')
// 			check_fill_quotes(str, '\'', msh);
// 		else if (str[msh->sh->i] == '"')
// 			check_fill_quotes(str, '"', msh);
// 		else if (str[msh->sh->i == '>'] || str[msh->sh->i == '>'])
// 			check_fill_redirections(str, msh);
// 		if (str[msh->sh->i] == '$')
// 		{
// 			name = ft_calloc(2, sizeof(char));
// 			name[0] = '$';
// 			msh->sh->i++;
// 			if ((ft_isdigit(str[msh->sh->i]) == 1)
// 				&& str[msh->sh->i - 1] == '$')
// 				msh->sh->i++;
// 			else
// 			{
// 				while (str[msh->sh->i] && str[msh->sh->i] != '$'
// 					&& ft_isalnum(str[msh->sh->i]) == 1)
// 				{
// 					name = ft_append_char(name, str[msh->sh->i]);
// 					msh->sh->i++;
// 				}
// 				ft_expand(msh->env, name);
// 				msh->sh->i--;
// 			}
// 			free(name);
// 		}
// 		msh->sh->i++;
// 		return (0);
// 	}
// 	return (0);
// }

/*
	count number of pipes
	malloc nodes and fill until number of pipes
	init struct
	malloc
	fill args each node
	fill command each node


	ignore dir
	ignore token
	ingnore cash
	ignore side
*/
int	parser_stage1(char *str, t_msh *msh)
{
	t_bool	ret;
	char	*name;

	ret = false;
	msh->sh->i = 0;
	msh->sh->euro = 0;
	while (str[msh->sh->i] && ret == false)
	{
		msh->sh->sq = 0;
		msh->sh->dq = 0;
		if (str[msh->sh->i] == '\'')
			ret = check_quotes(str, '\'', msh);
		else if (str[msh->sh->i] == '"')
			ret = check_quotes(str, '"', msh);
		else if (str[msh->sh->i == '>'] || str[msh->sh->i == '<'])
			ret = check_redirections(str, msh);
		if (str[msh->sh->i] == '$')
		{
			name = ft_calloc(2, sizeof(char));
			name[0] = '$';
			msh->sh->i++;
			if ((ft_isdigit(str[msh->sh->i]) == 1)
				&& str[msh->sh->i - 1] == '$')
				msh->sh->i++;
			else
			{
				while (str[msh->sh->i] && str[msh->sh->i] != '$'
					&& ft_isalnum(str[msh->sh->i]) == 1)
				{
					name = ft_append_char(name, str[msh->sh->i]);
					msh->sh->i++;
				}
				ft_expand(msh->env, name);
				msh->sh->i--;
			}
			free(name);
		}
		msh->sh->i++;
	}
	msh->sh->input_len = msh->sh->i;
	if (ret == false)
		return (0);
	else
		return (1);
}

int	ft_parse(char *str, t_msh *msh)
{
	if (!str)
		return (1);
	msh->sh = (t_sh *)malloc(sizeof(t_sh));
	if (parser_stage1(str, msh) == 0)
		ft_printf("valid\n");
		// parser_stage2(str, msh);
	free(msh->sh);
	return (1);
}
