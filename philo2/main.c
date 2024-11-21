/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:54:53 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/21 22:45:11 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments\n"));
	if (init_data(&data, argc, argv) || init_mutexes(&data)
		|| init_philos(&data))
		return (1);
	data.start_time = get_time();
	i = -1;
	while (++i < data.num_philos)
		if (pthread_create(&data.philos[i].thread, NULL, philo_routine,
				&data.philos[i]))
			return (1);
	while (!check_death(data.philos) && !check_meals(&data))
		usleep(1000);
	i = -1;
	while (++i < data.num_philos)
		pthread_join(data.philos[i].thread, NULL);
	clean_exit(&data);
	return (0);
}
