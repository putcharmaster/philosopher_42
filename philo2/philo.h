/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:45:56 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/21 22:27:59 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define SUCCESS 0
# define ERROR 1

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	int				dead;
	t_philo			*philos;
};

struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_data			*data;
};

/* init.c */
int			init_data(t_data *data, int argc, char **argv);
int			init_mutexes(t_data *data);
int			init_philos(t_data *data);

/* utils.c */
int			ft_atoi(const char *str);
long long	get_time(void);
void		ft_usleep(int ms);
void		print_status(t_data *data, int id, char *status);
void		clean_exit(t_data *data);

/* routine.c */
void		*philo_routine(void *arg);
int			philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

/* monitor.c */
int			check_death(t_philo *philo);
int			check_meals(t_data *data);

#endif