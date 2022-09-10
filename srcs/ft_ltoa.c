/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:44:13 by asanthos          #+#    #+#             */
/*   Updated: 2022/09/04 15:08:37 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ltoa(size_t n)
{
	size_t			i;
	char			*str;
	short			sign;
	size_t			pow_ten;

	i = 1;
	pow_ten = 1;
	sign = 0;
	++sign;
	while (n / pow_ten / 10 && i++)
		pow_ten *= 10;
	str = ft_calloc(i + sign + 1, 1);
	if (!str)
		return (NULL);
	i = 0;
	if (sign)
		str[i++] = '-';
	while (pow_ten)
	{
		str[i++] = n / pow_ten + '0';
		n = n % pow_ten;
		pow_ten /= 10;
	}
	return (str);
}