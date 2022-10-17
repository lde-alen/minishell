/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:25:21 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/17 22:14:04 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * count how many args
 * malloc first array
 * fill array [0] - done
 * finish filling the rest
 * parse the rest
 */

size_t	ft_fill_first_arg(t_lex *lex, size_t i, char *tmp)
{
	while (lex->cmd->command[i] && lex->cmd->command[i] != ' '
		&& lex->cmd->command[i] != '<' && lex->cmd->command[i] != '>'
		&& lex->cmd->command[i] != '|')
	{
		ft_append_back(&tmp, lex->cmd->command[i]);
		i++;
	}
	free (tmp);
	return (i);
}

char	*ft_args_to_str(t_lex *lex)
{
	size_t	i;
	char	*tmp;

	tmp = (char *)ft_calloc(1, sizeof(char));
	i = 0;
	while (i < ft_strlen(lex->cmd->command))
	{
		while (lex->cmd->command[i] == ' ' && lex->cmd->command[i])
			i++;
		if (lex->cmd->command[i] == D_QUOTE)
			fill_ds_quote(&tmp, &i, lex, D_QUOTE);
		if (lex->cmd->command[i] == S_QUOTE)
			fill_ds_quote(&tmp, &i, lex, S_QUOTE);
		if (lex->cmd->command[i] == '<' || lex->cmd->command[i] == '>')
			util_fill_redir(lex, &i);
		while (lex->cmd->command[i] == ' ' && lex->cmd->command[i + 1] == ' ')
			i++;
		while (lex->cmd->command[i] != '>'
			&& lex->cmd->command[i] != '<' && lex->cmd->command[i]
			&& lex->cmd->command[i] != D_QUOTE
			&& lex->cmd->command[i] != S_QUOTE)
		{
			ft_append_back(&tmp, lex->cmd->command[i]);
			i++;
		}
	}
	return (tmp);
}

size_t	ft_count_args(char *args)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (i < ft_strlen(args))
	{
		while (args[i] == ' ')
			i++;
		if (args[i] != ' ')
		{
			count++;
			while (args[i] && args[i] != ' ')
				i++;
			i--;
		}
		i++;
	}
	return (count);
}

void	ft_fill_arg(t_lex *lex)
{
	size_t	i;
	char	*args;
	char	*tmp;

	i = 0;
	tmp = ft_calloc(1, sizeof(char));
	i = ft_fill_first_arg(lex, i, tmp);
	args = ft_args_to_str(lex);
	lex->cmd->argument = splitaz(args, ' ');
	free(lex->cmd->command);
	free(args);
	lex->cmd->command = lex->cmd ->argument[0];
}

void	ft_init_file(char **file, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		file[i] = (char *)malloc(sizeof(char));
		file[i] = "";
		i++;
	}
	file[i] = NULL;
}
