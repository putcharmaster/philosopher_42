/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:20:08 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/20 20:38:42 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_all(t_data *data)
{
    for (int i = 0; i < data->args.num_philos; i++)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->print_lock);

    free(data->threads);
    free(data->forks);
    free(data->last_meal_times);
    free(data->meals_eaten);
}
