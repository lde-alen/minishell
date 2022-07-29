/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:18:54 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:12 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_itoa constructs a string representation of an integer. The
 * malloc'ed string representing the integer. NULL if the allocation fails.
 * 
 * @param n 
 * @return char* (FREE REQ)
 */
char	*ft_itoa(int n)
{
	size_t			i;
	char			*str;
	short			sign;
	unsigned int	pow_ten;

	i = 1;
	pow_ten = 1;
	sign = 0;
	if (n < 0 && ++sign)
		n = -n;
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
