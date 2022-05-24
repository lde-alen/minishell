/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 02:28:19 by lde-alen          #+#    #+#             */
/*   Updated: 2022/05/16 14:09:02 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief ft_atoi converts a string (ASCII values) into an int.
 * @param str
 * @return int
 */

static void	check_resaz(long long res)
{
	if (res > 2147483647 || res < -2147483648)
	{
		ft_putendl_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
}

int	ft_atoi(const char *str)
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
	check_resaz(res * neg);
	return (res * neg);
}
