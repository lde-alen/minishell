/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:50 by asanthos          #+#    #+#             */
/*   Updated: 2022/06/01 09:39:31 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(char *str, t_env *lst)
{
	if (str[0] == '$')
		ft_expander(lst, str);
	if (ft_strncmp(str, "echo", 4) == 0)
		ft_echo(str);
	if (strcmp(str, "pwd") == 0)
		ft_pwd(lst);
	if (strcmp(str, "env") == 0)
		print_list_env(lst);
}
