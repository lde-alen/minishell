/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:31:56 by lde-alen          #+#    #+#             */
/*   Updated: 2022/07/29 19:42:50 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_char_arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}
