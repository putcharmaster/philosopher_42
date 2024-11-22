/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:55 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/22 21:49:27 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	if (!s1 || !s2)
	{
		if (!s1 && !s2)
			return (0);
		if (!s1)
			return (-1);
		if (!s2)
			return (1);
	}
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (((unsigned char)(*s1) - (unsigned char)(*s2)));
}

void	print_status(t_data *data, int id, char *status)
{
	pthread_mutex_lock(&data->write_mutex);
	if (!data->dead || !ft_strcmp(status, "died"))
		printf("%lld %d %s\n", get_time() - data->start_time, id, status);
	pthread_mutex_unlock(&data->write_mutex);
}

void	clean_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	free(data->forks);
	free(data->philos);
}
