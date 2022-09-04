/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/04 23:16:05 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	
*/
int	parser_stage2(char *str, t_msh *msh)
{
	ft_printf("input_len value is: %d\n", msh->sh->input_len);
	msh->sh->tmp_str = ft_calloc(msh->sh->input_len + 1, sizeof(char));
	if (!msh->sh->tmp_str)
		return (0);
	msh->sh->i = 0;
	msh->sh->euro = 0;
	msh->sh->j = 0;
	while (msh->sh->i < ft_strlen(str))
	{

		if (str[msh->sh->i] == '\'' || str[msh->sh->i] == '"')
			check_fill_quotes(str, str[msh->sh->i], msh);
		else if (str[msh->sh->i] == '>' || str[msh->sh->i] == '<')
			check_redirections(str, msh);
		else if (str[msh->sh->i] == '|')
			check_p(str, msh);
		else if (str[msh->sh->i] == '$')
			ft_fill_expand(str, msh);
		else
			msh->sh->tmp_str[msh->sh->j] = str[msh->sh->i];
		msh->sh->i++;
		msh->sh->j++;

	}
	ft_printf("actual tmp_str is: %s\n", msh->sh->tmp_str);
	free(msh->sh->tmp_str);
	return (0);
}

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

	ret = false;
	msh->sh->i = 0;
	msh->sh->euro = 0;
	msh->sh->expand_len = 0;
	while (msh->sh->i < ft_strlen(str) && ret == false)
	{
		msh->sh->sq = 0;
		msh->sh->dq = 0;
		if (str[msh->sh->i] == '\'')
			ret = check_quotes(str, '\'', msh);
		else if (str[msh->sh->i] == '"')
			ret = check_quotes(str, '"', msh);
		else if (str[msh->sh->i] == '>' || str[msh->sh->i] == '<')
			ret = check_redirections(str, msh);
		else if (str[msh->sh->i] == '|')
			ret = check_p(str, msh);
		else if (str[msh->sh->i] == '$')
			ft_check_expand(str, msh);
		msh->sh->i++;
	}
	msh->sh->input_len = msh->sh->i + msh->sh->expand_len;
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
	if (!msh->sh)
		return (0);
	if (parser_stage1(str, msh) == 0)
		parser_stage2(str, msh);
	free(msh->sh);
	return (1);
}
