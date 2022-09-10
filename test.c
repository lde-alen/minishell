/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-alen <lde-alen@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:41:26 by lde-alen          #+#    #+#             */
/*   Updated: 2022/09/10 18:44:01 by lde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	i;

	i = 15;
	while (i > 0)
	{
		printf("\033[A\33[2KT\rAmount of seconds missing %d seconds...\n", i);
		i--;
		sleep(1);
	}
	return (0);
}
