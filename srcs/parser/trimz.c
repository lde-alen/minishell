/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:29:25 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/16 13:42:39 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_trim(char *str)
{
	size_t	i;
	size_t	len;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
			i++;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*ft_append_trim(char *name, char c)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len - 1)
	{
		str[i] = name[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(name);
	return (str);
}

char	*fill_trim(char *str)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("");
	while (str[i])
	{
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
			i++;
		else
		{
			tmp = ft_append_char(tmp, str[i]);
			i++;
		}
	}
	tmp = ft_append_char(tmp, '\0');
	free (str);
	return (tmp);
}

void	ft_trim_redir(char *str, t_cmd *tmp)
{
	size_t	i;

	i = 0;
	if (tmp->argument[0])
		tmp->command = ft_strdup(tmp->argument[0]);
	if (tmp->redir)
	{
		if (tmp->redir->file)
		{
			while (i < tmp->redir->flag_len)
			{
				str = fill_trim(tmp->redir->file[i]);
				tmp->redir->file[i] = ft_strdup(str);
				free(str);
				i++;
			}
		}
	}
}

void	trimaz(t_lex *lex)
{
	t_cmd	*tmp;
	size_t	i;
	char	*str;

	tmp = lex->cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->argument[i])
		{
			str = fill_trim(tmp->argument[i]);
			tmp->argument[i] = ft_strdup(str);
			free(str);
			i++;
		}
		ft_trim_redir(str, tmp);
		tmp = tmp->next;
	}
}
