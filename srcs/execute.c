/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:50 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/08 16:47:20 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//uncomment pipes & redirects when testing builtins
void	exec_cmd(t_env *lst, t_cmd *cmd_lst)
{
	// if (ft_strcmp(cmd_lst->argument[1], "<") == 0)
	// 	redirect_in(lst, cmd_lst);
	// else if (ft_strcmp(cmd_lst->argument[1], "<<") == 0)
	// 	here_doc(lst, cmd_lst);
	// else if (ft_strcmp(cmd_lst->argument[1], ">") == 0)
	// 	redirect_out(lst, cmd_lst);
	// else if (ft_strcmp(cmd_lst->argument[1], ">>") == 0)
	// 	append_out(lst, cmd_lst);
	exec_sys(lst, cmd_lst);
}
