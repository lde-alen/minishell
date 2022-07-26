/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 07:28:29 by asanthos          #+#    #+#             */
/*   Updated: 2022/07/26 11:27:06 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	char	**av;
	int		i;

	ft_printf("%d\n", get_args_len(cmd_lst));
	av = (char **)malloc(sizeof(char *) * get_args_len(cmd_lst));
	av[0] = cmd_lst->command;
	i = 0;
	while (cmd_lst->argument[i])
	{
		av[i + 1] = cmd_lst->argument[i];
		i++;
	}
	av[i + 1] = NULL;
	if (execve(cmd_lst->command, av, lst_to_char(lst)) < 0)
		perror("Execve problem");
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

void	check_execve(t_env *lst, t_cmd *cmd_lst)
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
			cmd_lst->argument[1] = ft_strdup(str);
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

