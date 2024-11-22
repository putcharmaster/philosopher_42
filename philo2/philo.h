/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:45:56 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/22 21:53:12 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
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
	pthread_mutex_t	meal_mutex;
	int				dead;
	t_philo			*philos;
}					t_data;

/* init.c */
int					init_data(t_data *data, int argc, char **argv);
int					init_mutexes(t_data *data);
int					init_philos(t_data *data);

/* utils_1.c */
void				clean_exit(t_data *data);
int					ft_strcmp(char const *s1, char const *s2);
void				print_status(t_data *data, int id, char *status);

/* utils_2.c */
int					ft_atoi(const char *str);
long long			get_time(void);
void				ft_usleep(int ms);

/* routine.c */
void				*philo_routine(void *arg);
int					philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

/* monitor.c */
int					check_all_deaths(t_data *data);
int					check_meals(t_data *data);

/* checker.c */
int					is_valid_int(char *str);
int					is_valid_input(int argc, char **argv);

#endif