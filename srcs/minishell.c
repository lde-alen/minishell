/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 23:43:24 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/10 23:13:52 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int val)
{
	if (val == SIGINT)
	{
		// ioctl(STDIN_FILENO, TIOCSTI);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 130;
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
		len++;
		i++;
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
		tmp = ft_append_char(tmp, str[i]);
		i++;
	}
	tmp = ft_append_char(tmp, '\0');
	free (str);
	return (tmp);
}

void	trimaz(t_lex *lex)
{
	t_cmd	*tmp;
	size_t	i;
	size_t	len;
	char	*str;

	len = 0;
	tmp = lex->cmd;
	while (tmp)
	{
		i = 0;
		while (tmp->argument[i])
		{
			len = count_trim(tmp->argument[i]);
			str = (char *)malloc(sizeof(char) * len + 1);
			str = fill_trim(tmp->argument[i]);
			tmp->argument[i] = ft_strdup(str);
			i++;
		}
		free(tmp->command);
		tmp->command = ft_strdup(tmp->argument[0]);
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
	ft_memset(&lex->env, 0, sizeof(t_env *));
	lex->env = ft_env(env);
	while (42)
	{
		str = readline("\e[0;37m|🐼| \e[1;35mminishell\e[0;37m$\e[0m ");
		if (str)
		{
			if (ft_strlen(str) >= 1)
			{
				add_history(str);
				if (ft_parse(str, lex) == 0)
				{
					trimaz(lex);
					ft_print_char_arr(lex->cmd->argument);
					exec_cmd(lex);
				}
			}
		}
		else
		{
			free_env_lst(lex->env);
			free (lex);
			exit(0);
		}
	}
}
