/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:59 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/22 21:29:14 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (philo->id % 2)
		usleep(philo->data->time_to_eat * 500);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (philo_eat(philo))
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo->data, philo->id, "has taken a fork");
	if (philo->data->num_philos == 1)
		return (pthread_mutex_unlock(philo->left_fork), 1);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo->data, philo->id, "has taken a fork");
	print_status(philo->data, philo->id, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo->data, philo->id, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo->data, philo->id, "is thinking");
}
