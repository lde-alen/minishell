/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 11:50:31 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/02 08:41:48 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_in(t_env *lst, t_cmd *cmd_lst)
{
	int	flag;
	int	status;

	flag = O_RDONLY;
	status = STDIN_FILENO;
	redirect(lst, cmd_lst, flag, status);
}

void	redirect_out(t_env *lst, t_cmd *cmd_lst)
{
	int	flag;
	int	status;

	flag = O_TRUNC | O_CREAT | O_WRONLY;
	status = STDOUT_FILENO;
	redirect(lst, cmd_lst, flag, status);
}

void	append_out(t_env *lst, t_cmd *cmd_lst)
{
	int	flag;
	int	status;

	flag = O_APPEND | O_WRONLY | O_CREAT;
	status = STDOUT_FILENO;
	redirect(lst, cmd_lst, flag, status);
}

void	here_doc(t_env *lst, t_cmd *cmd_lst)
{
	int		file;
	int		status;
	char	*str;

	file = open("store.txt", O_TRUNC | O_CREAT | O_RDWR);
	str = "";
	while (strcmp(str, cmd_lst->argument[2]) != 0)
	{
		str = readline("> ");
		ft_putendl_fd(str, file);
	}
	status = STDIN_FILENO;
	exec(lst, cmd_lst, status, file);
	close(file);
	unlink("store.txt");
}
