/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:53:18 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/04 11:48:05 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *str, int size)
{
	char	*tmp;
	int		i;

	i = 0;
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
