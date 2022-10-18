/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:46:42 by asanthos          #+#    #+#             */
/*   Updated: 2022/10/19 03:30:47 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_dash_val(t_env *lst)
{
	char	*store;
	char	*store_curr;
	ssize_t	ret;

	store_curr = ft_strdup(get_pwd());
	store = ft_strdup(search_env(lst, "OLDPWD")->value);
	free(search_env(lst, "OLDPWD")->value);
	search_env(lst, "OLDPWD")->value = ft_strdup(store_curr);
	ret = chdir(store);
	if (ret < 0)
		exit_stat(errno);
	else
	{
		if (search_env(lst, "PWD"))
		{
			free(search_env(lst, "PWD")->value);
			search_env(lst, "PWD")->value = ft_strdup(store);
		}
	}
	if (store)
		free(store);
	if (store_curr)
		free(store_curr);
	ft_putendl_fd(search_env(lst, "PWD")->value, 1);
}

void	set_err(t_cmd *cmd)
{
	struct stat	path_stat;

	if (stat(cmd->argument[1], &path_stat) == 0)
	{
		if (!S_ISDIR(path_stat.st_mode))
			err_msg(cmd->argument[1], ": Not a directory");
		else
			err_msg(cmd->argument[1], ": Permission denied");
	}
	else
		err_msg(cmd->argument[1], ": No such file or directory");
}
