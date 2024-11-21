/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:54:59 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/21 22:18:48 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/* routine.c */
void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        ft_usleep(philo->data->time_to_eat / 2);
    while (!check_death(philo))
    {
        if (philo_eat(philo))
            break;
        philo_sleep(philo);
        philo_think(philo);
    }
    return (NULL);
}

int philo_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo->data, philo->id, "has taken a fork");
    if (philo->data->num_philos == 1)
    {
        pthread_mutex_unlock(philo->left_fork);
        return (ERROR);
    }
    pthread_mutex_lock(philo->right_fork);
    print_status(philo->data, philo->id, "has taken a fork");
    print_status(philo->data, philo->id, "is eating");
    philo->last_meal_time = get_time();
    ft_usleep(philo->data->time_to_eat);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    return (SUCCESS);
}

void philo_sleep(t_philo *philo)
{
    print_status(philo->data, philo->id, "is sleeping");
    ft_usleep(philo->data->time_to_sleep);
}

void philo_think(t_philo *philo)
{
    print_status(philo->data, philo->id, "is thinking");
}
