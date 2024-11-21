/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:16:53 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/20 20:20:55 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// Get current timestamp in milliseconds
long long get_timestamp(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// Initialize the data structure
int init_data(t_data *data, t_args args)
{
    data->args = args;
    data->someone_died = 0;

    // Allocate memory for threads, forks, and arrays
    data->threads = malloc(sizeof(pthread_t) * args.num_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * args.num_philos);
    data->last_meal_times = malloc(sizeof(int) * args.num_philos);
    data->meals_eaten = malloc(sizeof(int) * args.num_philos);
    if (!data->threads || !data->forks || !data->last_meal_times || !data->meals_eaten)
        return (1);

    // Initialize forks and arrays
    for (int i = 0; i < args.num_philos; i++)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        data->last_meal_times[i] = 0;
        data->meals_eaten[i] = 0;
    }
    pthread_mutex_init(&data->print_lock, NULL);
    return (0);
}
