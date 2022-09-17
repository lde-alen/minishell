/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:48:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/17 17:00:52 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next != env)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

ssize_t	get_expand_len(char *name, t_env *env, int flag)
{
	ssize_t	len;
	size_t	len_name;
	size_t	len_value;

	len = 0;
	if (flag == 1)
	{
		len_name = ft_strlen(name);
		len_value = ft_strlen(ft_itoa(g_exit));
	}
	else
	{
		len_name = ft_strlen(name);
		len_value = ft_strlen(get_env_value(env, name + 1));
	}
	if (len_value == 0)
		return (0);
	len = len_value - len_name;
	return (len);
}

char	*ft_expand(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (ft_strcmp(lst->name, ft_strchr(str, str[1])) == 0)
			return (lst->value);
		lst = lst->next;
	}
	lst = tmp;
	return (NULL);
}

char	*ft_append_char(char *name, char c)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name) + 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len - 1)
	{
		str[i] = name[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(name);
	return (str);
}
