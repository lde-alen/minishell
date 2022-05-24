/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asc_to_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:49:43 by lde-alen          #+#    #+#             */
/*   Updated: 2022/03/17 17:14:55 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_get_char(unsigned long long int nb, int hex)
{
	if (nb < 10)
		return (nb + '0');
	if (nb >= 10)
	{
		if (hex == 0 || hex == 1)
			return (nb + 87);
		else
			return (nb + 55);
	}
	return (0);
}

char	*ft_asc_to_hex(char *str, int i, unsigned long int nb, int hex)
{
	unsigned long int	j;

	j = 0;
	while (nb != 0)
	{
		j = nb % 16;
		str[i] = ft_get_char(j, hex);
		nb /= 16;
		i--;
	}
	return (str);
}
