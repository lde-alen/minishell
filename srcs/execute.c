/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:08:50 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/23 10:09:22 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_lst_len(t_env *lst)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (lst->next != tmp)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**lst_to_char(t_env *lst)
{
	char	**env;
	char	*temp_str;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	temp_str = "";
	env = (char **)malloc(sizeof(char *) * get_lst_len(lst));
	while (lst->next != tmp)
	{
		env[i] = lst->name;
		temp_str = ft_strjoin(env[i], "=");
		env[i] = ft_strjoin(temp_str, lst->value);
		// free(temp_str);
		lst = lst->next;
		i++;
	}
	return (env);
}

char	**get_path(t_env *lst)
{
	char	**env_path;
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (strcmp(lst->name, "PATH") == 0)
		{
			env_path = ft_split(lst->value, ':');
			return (env_path);
		}
		lst = lst->next;
	}
	return NULL;
}

void	main_child(t_env *lst, t_cmd *cmd_lst)
{
	execve(cmd_lst->command, cmd_lst->argument, lst_to_char(lst));
}

void	check_exec(t_env *lst, t_cmd *cmd_lst)
{
	char	**env_path;
	char	*post_join;
	char	*str;
	int		id;
	int		i;

	i = 0;
	env_path = get_path(lst);
	while (env_path[i])
	{
		post_join = ft_strjoin("/", cmd_lst->command);
		str = ft_strjoin(env_path[i], post_join);
		if (access(str, F_OK) == 0)
		{
			free(cmd_lst->command);
			cmd_lst->command = ft_strdup(str);
			id = fork();
			if (id < 0)
				ft_putendl_fd("Fork failed", 2);
			else if (id == 0)
				main_child(lst, cmd_lst);
			waitpid(-1, NULL, 0);
			free(str);
			free(post_join);
		}
		i++;
	}
}

void	exec_cmd(t_env *lst, t_cmd *cmd_lst)
{
	if (cmd_lst->command[0] == '$')
		ft_expander(lst, cmd_lst->command);
	else if (strcmp(cmd_lst->command, "echo") == 0)
		ft_echo(cmd_lst);
	else if (strcmp(cmd_lst->command, "pwd") == 0)
		ft_pwd(lst);
	else if (strcmp(cmd_lst->command, "env") == 0)
		print_list_env(lst);
	else if (strcmp(cmd_lst->command, "export") == 0 && cmd_lst->argument[0] != NULL)
		ft_export(lst, cmd_lst);
	else if (strcmp(cmd_lst->command, "export") == 0)
		lonely_export(lst);
	else if (strcmp(cmd_lst->command, "unset") == 0)
		ft_unset(lst, cmd_lst);
	else if (strcmp(cmd_lst->command, "cd") == 0)
		ft_cd(cmd_lst, lst);
	else if (ft_strncmp(cmd_lst->command, "exit", 4) == 0)
		exit(0);
	else
		check_exec(lst, cmd_lst);
}
