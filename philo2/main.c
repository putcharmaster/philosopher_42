/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:54:53 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/22 18:26:00 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int print_error_1(void)
{
    printf("Error: wrong number of arguments\n");
    printf("Usage: number_of_philosophers, time_to_die, \
time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
    return (1);
}

static int print_error_2(void)
{
    printf("Error: arguments must be valid integers\n");
    printf("Usage: number_of_philosophers, time_to_die, \
time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]\n");
    return (1);
}
int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
		return (print_error_1());
	if (!is_valid_input(argc, argv))
		return (print_error_2());
	if (init_data(&data, argc, argv) || init_mutexes(&data)
		|| init_philos(&data))
		return (1);
	data.start_time = get_time();
	i = -1;
	while (++i < data.num_philos)
		if (pthread_create(&data.philos[i].thread, NULL, philo_routine,
				&data.philos[i]))
			return (1);

	// Wait for death or all meals eaten
	while (!check_all_deaths(&data) && !check_meals(&data))
		usleep(100);
	
    // Set dead flag to make all threads exit
	pthread_mutex_lock(&data.death_mutex);
	data.dead = 1;
	pthread_mutex_unlock(&data.death_mutex);
	
    // Now wait for all threads to finish
	i = -1;
	while (++i < data.num_philos)
		pthread_join(data.philos[i].thread, NULL);
	clean_exit(&data);
	return (0);
}
