/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 03:20:34 by lde-alen          #+#    #+#             */
/*   Updated: 2021/12/23 13:29:27 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs the character ’c’ to the given file descriptor.
 * 
 * @param c 
 * @param fd 
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
