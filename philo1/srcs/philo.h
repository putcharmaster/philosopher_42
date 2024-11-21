/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:01:54 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/20 20:56:16 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

// Structure for input arguments
typedef struct s_args
{
    int num_philos;       // Number of philosophers
    int time_to_die;      // Time before a philosopher dies
    int time_to_eat;      // Time to eat
    int time_to_sleep;    // Time to sleep
    int max_meals;        // Max meals a philosopher can eat (-1 for no limit)
}   t_args;

// Shared data structure
typedef struct s_data
{
    int id;
    t_args args;                  // Input arguments
    pthread_t *threads;           // Philosopher threads
    pthread_mutex_t *forks;       // Mutexes for forks
    int *last_meal_times;         // Last meal timestamp for each philosopher
    int *meals_eaten;             // Meals eaten by each philosopher
    int someone_died;             // Flag to indicate if a philosopher has died
    pthread_mutex_t print_lock;   // Mutex for printing
}   t_data;

// Function prototypes
int         init_data(t_data *data, t_args args);
void        *philosopher_routine(void *arg);
long long   get_timestamp(void);
void        print_status(t_data *data, int id, const char *message);
void        free_all(t_data *data);
int         ft_atoi(char *str);

#endif
