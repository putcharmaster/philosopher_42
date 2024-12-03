/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:53 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/22 19:42:34 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	has_input_error(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Error: wrong number of arguments\n");
		printf("Usage: number_of_philosophers, time_to_die, \
time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (!is_valid_input(ac, av))
	{
		printf("Error: arguments must be valid integers\n");
		printf("Usage: number_of_philosophers, time_to_die, \
time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (has_input_error(ac, av))
		return (1);
	if (init_data(&data, ac, av) || init_mutexes(&data) || init_philos(&data))
		return (1);
	data.start_time = get_time();
	i = -1;
	while (++i < data.num_philos)
		if (pthread_create(&data.philos[i].thread, NULL, philo_routine,
				&data.philos[i]))
			return (1);
	while (!check_all_deaths(&data) && !check_meals(&data))
		usleep(100);
	pthread_mutex_lock(&data.death_mutex);
	data.dead = 1;
	pthread_mutex_unlock(&data.death_mutex);
	i = -1;
	while (++i < data.num_philos)
		pthread_join(data.philos[i].thread, NULL);
	clean_exit(&data);
	return (0);
}
