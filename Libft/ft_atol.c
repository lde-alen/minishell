/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 05:26:13 by asanthos          #+#    #+#             */
/*   Updated: 2022/08/02 05:50:37 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_atoi converts a string (ASCII values) into a long.
 * @param str
 * @return long
 */

static void	check_resaz(long long res)
{
	if (res > 9223372036854775807)
	{
		ft_putendl_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
}

long	ft_atoi(const char *str)
{
	int				i;
	int				neg;
	long long		res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\n'
		|| str[i] == '\f' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			neg = -1;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res * neg);
}