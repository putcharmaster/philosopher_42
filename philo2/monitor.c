/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:54:44 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/21 23:03:31 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead || (get_time()
			- philo->last_meal_time > philo->data->time_to_die))
	{
		if (!philo->data->dead)
		{
			philo->data->dead = 1;
			print_status(philo->data, philo->id, "died");
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

int	check_meals(t_data *data)
{
	int	i;

	i = -1;
	if (data->must_eat_count == -1)
		return (0);
	while (++i < data->num_philos)
		if (data->philos[i].meals_eaten < data->must_eat_count)
			return (0);
	return (1);
}
