/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:00:39 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/22 21:26:19 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_int(char *str)
{
	int	i;
	int	plus_count;

	i = 0;
	plus_count = 0;
	while (str[i])
	{
		if (str[i] == '+')
			plus_count++;
		else if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i == 0 || plus_count > 1)
		return (0);
	return (1);
}

int	is_valid_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
