/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:14:43 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/18 14:35:21 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_guy(int flag)
{
	static int	value;

	if (flag == 0)
	{
		ft_putendl_fd(ft_itoa(value), 2);
		if (value == -10)
			g_exit = 130;
		else
			g_exit = 1;
	}
	else
		value = flag;
}

void	sig_handler(int val)
{
	handler_guy(0);
	if (val == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (g_exit == -69)
			g_exit = 130;
		else
			g_exit = 1;
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
}
