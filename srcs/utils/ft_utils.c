/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:53:18 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/03 20:03:12 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strjustlcat(char *dst, const char *src, size_t len)
{
	char	*tmp_src;
	size_t	len_dest;
	size_t	i;

	tmp_src = (char *)src;
	len_dest = ft_strlen(dst);
	i = 0;
	while (i < len)
	{
		dst[len_dest] = tmp_src[i];
		len_dest++;
		i++;
	}
}
