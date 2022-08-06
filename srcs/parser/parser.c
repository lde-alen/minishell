/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:34:20 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/06 06:21:51 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_init(t_cmd **cmd, t_env **env)
{
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	*env = (t_env *)malloc(sizeof(t_env));
	(*cmd)->command = NULL;
	(*cmd)->token = -1;
	(*cmd)->side = 0;
	(*cmd)->next = NULL;
	(*env)->name = NULL;
	(*env)->value = NULL;
	(*env)->prev = *env;
	(*env)->next = *env;
	return (1);
}

int	ft_fill_arg(char ***argument, char *str)
{
	if (!argument)
		return (-1);
	*argument = ft_split(str, ' ');
	return (1);
}

int	ft_fill_cmd(char **command, char **argument)
{
	if (!argument[0])
		return (-1);
	*command = argument[0];
	return (1);
}

int	check_dq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if ((ft_strchr(str + (i + 1), '\"') != NULL))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_sq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if ((ft_strchr(str + (i + 1), '\'') != NULL))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_srr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			while (str[++i])
			{
				if (str[i] > ' ' && str[i] <= '~')
					return (1);
			}
			i--;
		}
		i++;
	}
	return (0);
}

int	check_slr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			while (str[++i])
			{
				if (str[i] > ' ' && str[i] <= '~')
					return (1);
			}
			i--;
		}
		i++;
	}
	return (0);
}

int	check_p(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			while (str[++i])
			{
				if (str[i] > ' ' && str[i] <= '~')
					return (1);
			}
			i--;
		}
		i++;
	}
	return (0);
}

int	check_drr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
		{
			while (str[++i])
			{
				if (str[i] > ' ' && str[i] <= '~')
					return (1);
			}
			i--;
		}
		i++;
	}
	return (0);
}

int	check_dlr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			while (str[++i])
			{
				if (str[i] > ' ' && str[i] <= '~')
					return (1);
			}
			i--;
		}
		i++;
	}
	return (0);
}

int	ft_parse(char *str, char **src_env)
{
	t_cmd	*cmd;
	t_env	*env;

	(void)src_env;
	(void)*cmd;
	(void)*env;
	ft_printf("%d\n", check_dq(str));
	ft_printf("%d\n", check_sq(str));
	ft_printf("%d\n", check_srr(str));
	ft_printf("%d\n", check_slr(str));
	ft_printf("%d\n", check_p(str));
	// ft_printf("%d\n", check_sq(str));
	// ft_init(&cmd, &env);
	// ft_fill_arg(&cmd->argument, str);
	// ft_fill_cmd(&cmd->command, &cmd->argument[0]);
	// ft_printf("Original str:\n%s\n", str);
	// ft_printf("User input is:\n");
	// ft_print_char_arr(cmd->argument);
	// ft_printf("Command is:\n");
	// ft_printf(("%s\n"), cmd->command);
	return (1);
}
