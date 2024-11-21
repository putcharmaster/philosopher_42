/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:01:25 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/20 20:38:53 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_args args;
    t_data data;

    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s num_philos time_to_die time_to_eat time_to_sleep [max_meals]\n", argv[0]);
        return (1);
    }

    // Parse arguments
    args.num_philos = ft_atoi(argv[1]);
    args.time_to_die = ft_atoi(argv[2]);
    args.time_to_eat = ft_atoi(argv[3]);
    args.time_to_sleep = ft_atoi(argv[4]);
    args.max_meals = (argc == 6) ? ft_atoi(argv[5]) : -1;

    // Initialize data
    if (init_data(&data, args))
    {
        printf("Failed to initialize data.\n");
        return (1);
    }

    // Create philosopher threads
    for (int i = 0; i < args.num_philos; i++)
        pthread_create(&data.threads[i], NULL, philosopher_routine, (void *)(size_t)i);

    // Monitor threads (optional: implement death checking here)
    for (int i = 0; i < args.num_philos; i++)
        pthread_join(data.threads[i], NULL);

    // Cleanup
    free_all(&data);
    return (0);
}
