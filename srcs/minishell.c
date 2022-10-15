/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:43:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/15 20:12:02 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_loop(t_lex *lex, char *str)
{
	if (str)
	{
		if (ft_strlen(str) >= 1)
		{
			add_history(str);
			if (ft_parse(str, lex) == 0)
			{
				if (lex->cmd)
				{
					if (lex->cmd->argument)
					{
						if (!lex->cmd->command && !lex->cmd->next
							&& !lex->cmd->redir)
						{
							ft_printf("FREE INVALID\n");
							while (lex->cmd)
								free_cmd(&lex->cmd);
							return ;
						}
						trimaz(lex);
						exec_sys(lex);
					}
					else
						free_cmd(&lex->cmd);
				}
			}
		}
	}
	else
	{
		if (lex->cmd)
			if (lex->cmd->redir)
				free_child(lex);
		free(lex->cmd);
		free_env_lst(lex->env);
		free (lex);
		exit(g_exit);
	}
}

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
		tmp = tmp->next;
	}
}

int	minishell(char **env)
{
	t_lex	*lex;
	char	*str;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	lex = (t_lex *)malloc(sizeof(t_lex));
	if (!lex)
		exit(EXIT_FAILURE);
	ft_memset(&lex->env, 0, sizeof(t_env *));
	lex->env = ft_env(env);
	while (42)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		mini_loop(lex, str);
	}
}
