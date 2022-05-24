/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:20:47 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:28 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks for the int limits as we are dealing only with integers.
 * 
 * @param n 
 * @param fd 
 */
static void	ft_limits(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
		ft_putchar_fd('0', fd);
}

/**
 * @brief Outputs the integer ’n’ to the given file descriptor.
 * 
 * @param n 
 * @param fd 
 */
void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	c[10];

	if (fd < 0)
		return ;
	if (n == 0 || n == -2147483648)
	{
		ft_limits(n, fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	i = 0;
	while (n > 0)
	{
		c[i] = n % 10 + '0';
		n = n / 10;
		i++;
	}
	i--;
	while (i >= 0)
		ft_putchar_fd(c[i--], fd);
}
