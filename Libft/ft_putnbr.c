/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:49:00 by lde-alen          #+#    #+#             */
/*   Updated: 2022/03/17 17:16:53 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_nblen(long int n)
{
	int	i;

	i = 1;
	if (n > 0)
		i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr(long int nb)
{
	int	resultaz;

	resultaz = ft_nblen(nb);
	if (nb == -2147483648)
	{
		ft_putstr("-2147483648");
		return (resultaz);
	}
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar('-');
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
	return (resultaz);
}
