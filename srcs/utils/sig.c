/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:14:43 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/17 15:01:54 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int val)
{
	if (val == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit = 130;
	}
}

void	sig(int val)
{
	if (val == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_redisplay();
		g_exit = -69;
	}
}

void	free_sig(t_redir *redir, char *store)
{
	free(store);
	if (redir->str || ft_strcmp(redir->str, "") == 0)
		free(redir->str);
	if (redir->doc_arr)
	{
		int i = 0;
		while (redir->doc_arr[i])
			free(redir->doc_arr[i]);
		free(redir->doc_arr);
	}
}
