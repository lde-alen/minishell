/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:04:31 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/03 20:36:40 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*tmp;
	int		len;
	int		neg;

	tmp = (char *)str;
	neg = 1;
	if (str[0] == '-')
	{
		neg = -1;
		str++;
	}
	res = (double)ft_atoi(tmp);
	while (*tmp && *tmp != '.')
		tmp++;
	if (*tmp == '.')
		tmp++;
	res2 = (double)ft_atoi(tmp);
	len = ft_strlen(tmp);
	while (len--)
		res2 /= 10;
	if (neg == -1)
		return (res - res2);
	return (res + res2);
}
