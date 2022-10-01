/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 12:45:57 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/01 16:59:25 by asanthos         ###   ########.fr       */
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
			err_msg(lex->cmd, "warning",
				"shell level too high, resetting to 1");
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
	if (errno == 2)
	{
		g_exit = 127;
		return (g_exit);
	}
	else if (errno == 13 || errno == 20)
	{
		g_exit = 126;
		return (g_exit);
	}
	return (0);
}
