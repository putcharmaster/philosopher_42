/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:18:28 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/20 20:56:39 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Print a synchronized message
void print_status(t_data *data, int id, const char *message)
{
    pthread_mutex_lock(&data->print_lock);
    if (!data->someone_died)
        printf("%lld %d %s\n", get_timestamp(), id + 1, message);
    pthread_mutex_unlock(&data->print_lock);
}
void *philosopher_routine(void *arg)
{
    if (!arg) {
        printf("Error: philosopher routine received NULL argument.\n");
        return NULL;
    }

    t_data *data = (t_data *)arg;
    int id = data->id;  // Use ID stored in data

    while (!data->someone_died)
    {
        // Pick up forks (lock forks in a safe order)
        int first_fork = id;
        int second_fork = (id + 1) % data->args.num_philos;

        if (first_fork > second_fork) {
            int temp = first_fork;
            first_fork = second_fork;
            second_fork = temp;
        }

        pthread_mutex_lock(&data->forks[first_fork]);
        pthread_mutex_lock(&data->forks[second_fork]);

        print_status(data, id, "is eating");

        // Update last meal time and meals eaten
        data->last_meal_times[id] = get_timestamp();
        data->meals_eaten[id]++;
        
        // Simulate eating with usleep
        struct timespec ts;
        ts.tv_sec = 0;
        ts.tv_nsec = data->args.time_to_eat * 1000;
        nanosleep(&ts, NULL);

        // Put down forks
        pthread_mutex_unlock(&data->forks[first_fork]);
        pthread_mutex_unlock(&data->forks[second_fork]);

        // Sleep
        print_status(data, id, "is sleeping");
        ts.tv_nsec = data->args.time_to_sleep * 1000;
        nanosleep(&ts, NULL);

        // Think
        print_status(data, id, "is thinking");
    }

    return (NULL);
}

// // Philosopher routine
// void *philosopher_routine(void *arg)
// {
//     t_data *data = (t_data *)arg;
//     int id = (int)(size_t)arg; // Cast philosopher ID

//     while (!data->someone_died)
//     {
//         // Pick up forks
//         pthread_mutex_lock(&data->forks[id]);
//         pthread_mutex_lock(&data->forks[(id + 1) % data->args.num_philos]);
//         print_status(data, id, "is eating");

//         // Update last meal time and meals eaten
//         data->last_meal_times[id] = get_timestamp();
//         data->meals_eaten[id]++;
//         usleep(data->args.time_to_eat * 1000);

//         // Put down forks
//         pthread_mutex_unlock(&data->forks[id]);
//         pthread_mutex_unlock(&data->forks[(id + 1) % data->args.num_philos]);

//         // Sleep
//         print_status(data, id, "is sleeping");
//         usleep(data->args.time_to_sleep * 1000);

//         // Think
//         print_status(data, id, "is thinking");
//     }
//     return (NULL);
// }
