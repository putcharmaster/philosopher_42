/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:54:51 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/21 22:18:23 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/* init.c */
int init_data(t_data *data, int argc, char **argv)
{
    data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->must_eat_count = (argc == 6) ? ft_atoi(argv[5]) : -1;
    data->dead = 0;
    
    if (data->num_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
        || data->time_to_sleep < 0 || (argc == 6 && data->must_eat_count < 0))
        return (ERROR);
        
    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    if (!data->philos)
        return (ERROR);
    return (SUCCESS);
}

int init_mutexes(t_data *data)
{
    int i;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    if (!data->forks)
        return (ERROR);
        
    i = -1;
    while (++i < data->num_philos)
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (ERROR);
            
    if (pthread_mutex_init(&data->write_mutex, NULL)
        || pthread_mutex_init(&data->death_mutex, NULL))
        return (ERROR);
    return (SUCCESS);
}

int init_philos(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->num_philos)
    {
        data->philos[i].id = i + 1;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = get_time();
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
        data->philos[i].data = data;
    }
    return (SUCCESS);
}
