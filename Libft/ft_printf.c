/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:49:16 by lde-alen          #+#    #+#             */
/*   Updated: 2022/03/17 17:15:43 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fptr_init(int ((**fptr)(va_list ap)))
{
	fptr[0] = &ft_printf_putchar;
	fptr[1] = &ft_printf_putstr;
	fptr[2] = &ft_printf_ptr;
	fptr[3] = &ft_printf_putnbr;
	fptr[4] = &ft_printf_putnbr;
	fptr[5] = &ft_printf_putnbr_u;
	fptr[6] = &ft_printf_hexa;
	fptr[7] = &ft_printf_hexo;
	fptr[8] = &ft_printf_percentage;
}

static int	ft_check_flag(char c)
{
	int		i;
	char	*flag;

	i = 0;
	flag = "cspdiuxX%";
	while (flag[i])
	{
		if (flag [i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		result;
	int		(*fptr[9])(va_list ap);

	i = 0;
	va_start(ap, format);
	fptr_init(fptr);
	result = 0;
	while (format[i])
	{
		if (format[i] == '%' && ft_check_flag(format[i + 1]) != -1)
		{
			result += fptr[ft_check_flag(format[i + 1])](ap);
			i++;
		}
		else
		{
			ft_putchar(format[i]);
			result++;
		}
		i++;
	}
	va_end(ap);
	return (result);
}
