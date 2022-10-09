/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:45:57 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/09 14:21:59 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(t_lex *lex, t_exec *exec)
{
	char	*val;
	int		shl_val;

	if (exec->path != NULL && ft_strcmp(exec->path, "./minishell") == 0
		&& search_env(lex->env, "SHLVL")->value != NULL)
	{
		val = search_env(lex->env, "SHLVL")->value;
		shl_val = ft_atoi(val);
		free(val);
		if (shl_val < 0)
			search_env(lex->env, "SHLVL")->value = ft_strdup("0");
		else if (shl_val < 999)
			search_env(lex->env, "SHLVL")->value = ft_itoa(shl_val + 1);
		else if (shl_val == 999)
			search_env(lex->env, "SHLVL")->value = NULL;
		else
		{
			err_msg("warning", "shell level too high, resetting to 1");
			search_env(lex->env, "SHLVL")->value = ft_strdup("1");
		}
	}
	else if (search_env(lex->env, "SHLVL")->value == NULL)
		search_env(lex->env, "SHLVL")->value = ft_strdup("1");
}

t_bool	check_here_doc(t_lex *lex)
{
	size_t	i;

	i = 0;
	while (i < lex->cmd->redir->flag_len)
	{
		if (lex->cmd->redir->flag[i] == DL_REDIR)
			return (true);
		i++;
	}
	return (false);
}

size_t	exit_stat(int err)
{
	perror("minishell");
	ft_printf("Errno: %d\n", err);
	if (err == 2)
	{
		g_exit = 1;
		return (g_exit);
	}
	else if (err == 13 || err == 20)
	{
		g_exit = 126;
		return (g_exit);
	}
	return (0);
}

void	wait_stat(void)
{
	signal(SIGINT, SIG_IGN);
	wait(&g_exit);
	signal(SIGINT, sig_handler);
	if (WIFEXITED(g_exit))
		g_exit = WEXITSTATUS(g_exit);
}

void	init_null(t_lex *lex)
{
	lex->exec->env_kid = NULL;
	lex->exec->path = NULL;
}
