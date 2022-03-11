/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:50:11 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/11 14:05:59 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_someone_die__time_to_die(t_data *data)
{
	int		i;
	time_t	curent_time;
	int		all_still_alive;

	all_still_alive = 1;
	usleep(1000);
	while (all_still_alive)
	{
		curent_time = get_curent_time_in_msec();
		i = 0;
		while (i < data->num_of_philo)
		{
			if (curent_time - data->last_meal[i] > data->time_to_die)
			{
				printf("%7ld: %d died\n", curent_time, i + 1);
				all_still_alive = 0;
			}
			i++;
		}
	}
}

static void	check_someone_die__meal_count(t_data *data)
{
	int	i;
	int	all_still_alive;

	all_still_alive = 1;
	usleep(1000);
	while (all_still_alive)
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			if (data->last_meal[i] < data->meal_count)
			{
				all_still_alive = 1;
				break ;
			}
			else
			{
				all_still_alive = 0;	
			}
			i++;
		}
	}
}

int main(int argc, char **argv)
{
	t_data		**data_args;
	t_data		*data;
	pthread_t	*threads;
	int			i;

	if (argc != 5 && argc != 6)
		return 0;
	data_args = initialising_data(argv + 1);
	data = data_args[0];
	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->num_of_philo);
	if (! threads)
		perror_then_exit(MALLOC_ERROR);
	i = 0;
	while (i < data->num_of_philo)
	{
		if (data->meal_count < 0)
			data->last_meal[i] = get_curent_time_in_msec();
		else
			data->last_meal[i] = 0;
		pthread_create(threads + i, NULL, philosopher, data_args + i);
		i++;
	}
	if (data->meal_count < 0)
		check_someone_die__time_to_die(data);
	else
		check_someone_die__meal_count(data);

	free(data->last_meal);
	free(data->mutexs);
	free(threads);
	free(data);
	free(data_args);
	return 0;
}
