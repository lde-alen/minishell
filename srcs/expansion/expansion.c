/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 09:48:07 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/13 19:52:02 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand(t_env *lst, char *str)
{
	t_env	*tmp;

	tmp = lst;
	while (lst->next != tmp)
	{
		if (ft_strcmp(lst->name, ft_strchr(str, str[1])) == 0)
		{
			ft_putendl_fd(lst->value, 1);
		}
		lst = lst->next;
	}
	if (ft_strcmp(lst->name, ft_strchr(str, str[1])) == 0)
		ft_putendl_fd(lst->value, 1);
	lst = tmp;
}

char	*ft_append_char(char *name, char c)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(name);
	str = (char *)malloc(sizeof(char) * (len + 2));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = name[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(name);
	return (str);
}
