/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:44 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/22 19:28:41 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_deaths(t_data *data)
{
	int			i;
	long long	current_time;
	long long	last_meal;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		pthread_mutex_lock(&data->meal_mutex);
		current_time = get_time();
		last_meal = data->philos[i].last_meal_time;
		if (!data->dead && (current_time - last_meal > data->time_to_die))
		{
			data->dead = 1;
			print_status(data, data->philos[i].id, "died");
			pthread_mutex_unlock(&data->meal_mutex);
			pthread_mutex_unlock(&data->death_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		pthread_mutex_unlock(&data->death_mutex);
	}
	return (0);
}

int	check_meals(t_data *data)
{
	int	i;
	int	meals;

	i = -1;
	if (data->must_eat_count == -1)
		return (0);
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		meals = data->philos[i].meals_eaten;
		pthread_mutex_unlock(&data->meal_mutex);
		if (meals < data->must_eat_count)
			return (0);
	}
	return (1);
}
