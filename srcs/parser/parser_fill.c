/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:25:21 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/12 16:00:15 by lde-alen         ###   ########.fr       */
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
	return (i);
}

/**
 * should be fine
 */
char	*ft_args_to_str(t_lex *lex)
{
	size_t	i;
	char	*tmp;

	tmp = (char *)ft_calloc(1, sizeof(char));
	i = 0;
	while (i < ft_strlen(lex->cmd->command))
	{
		while (lex->cmd->command[i] == ' ')
			i++;
		if (lex->cmd->command[i] == '<' || lex->cmd->command[i] == '>')
		{
			i++;
			if (lex->cmd->command[i] == '<' || lex->cmd->command[i] == '>')
				i++;
			while (lex->cmd->command[i] == ' ')
				i++;
			while ((lex->cmd->command[i] != ' ' && lex->cmd->command[i] != '>'
					&& lex->cmd->command[i] != '<'
					&& lex->cmd->command[i] != '|')
				&& lex->cmd->command[i])
					i++;
		}
		while (lex->cmd->command[i] == ' ')
			i++;
		while (lex->cmd->command[i] != ' ' && lex->cmd->command[i] != '>'
			&& lex->cmd->command[i] != '<' && lex->cmd->command[i] != '|'
			&& lex->cmd->command[i])
		{
			ft_append_back(&tmp, lex->cmd->command[i]);
			i++;
		}
		i--;
		tmp = ft_strjoin(tmp, " ");
		i++;
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
		}
		i++;
	}
	return (count);
}

void	ft_fill_arg(t_lex *lex)
{
	size_t	i;
	size_t	nb_args;
	char	*args;
	char	*tmp;

	i = 0;
	tmp = ft_calloc(1, sizeof(char));
	i = ft_fill_first_arg(lex, i, tmp);
	args = ft_args_to_str(lex);
	nb_args = ft_count_args(args);
	lex->cmd->argument = (char **)malloc(sizeof(char *) * (nb_args + 1));
	lex->cmd ->argument = ft_split(args, ' ');
	free(lex->cmd->command);
	lex->cmd->command = lex->cmd ->argument[0];
	ft_printf("*command: %s\n", lex->cmd->command);
	ft_printf("string with all args: %s\n", args);
	ft_printf("the nb of args is: %d\n", nb_args);
	ft_printf("the value of i is: %d\n", i);
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
