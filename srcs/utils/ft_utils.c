/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:53:18 by lde-alen          #+#    #+#             */
/*   Updated: 2022/10/08 19:27:50 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *str, int size)
{
	char	*tmp;
	int		i;

	i = 0;
	(void)size;
	tmp = (char *)malloc(sizeof(char) * size);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	free(str);
	return (tmp);
}

void	ft_strjustcat(char *dst, const char *src)
{
	char	*tmp_src;
	size_t	len_dest;
	size_t	i;

	tmp_src = (char *)src;
	len_dest = ft_strlen(dst);
	i = 0;
	if (dst == NULL || src == NULL)
		return ;
	while (tmp_src[i])
	{
		dst[len_dest] = tmp_src[i];
		len_dest++;
		i++;
	}
}

void	ft_append_back(char **str, char c)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(*str) + 2));
	while ((*str)[i])
	{
		tmp[i] = (*str)[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	if (*str)
		free (*str);
	*str = ft_strdup(tmp);
	free(tmp);
}
