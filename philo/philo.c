/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:50:11 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/12 13:30:20 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_someone_die__time_to_die(t_data *data)
{
	int		i;
	time_t	curent_time;

	usleep(1000);
	while (1)
	{
		curent_time = get_curent_time_in_msec();
		i = 0;
		while (i < data->num_of_philo)
		{
			if (curent_time - data->last_meal[i] > data->time_to_die)
			{
				pthread_mutex_lock(data->print_turn);
				printf("%ld: %d died\n", curent_time, i + 1);
				return ;
			}
			i++;
		}
		usleep(1000);
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
				all_still_alive = 0;
			i++;
		}
		usleep(500);
	}
}

static void	check_time_to_die__or__meal_count(t_data *data)
{
	if (data->meal_count < 0)
		check_someone_die__time_to_die(data);
	else
		check_someone_die__meal_count(data);
}

int	main(int argc, char **argv)
{
	t_data		**data_args;
	t_data		*data;
	pthread_t	*threads;
	int			i;

	if (argc != 5 && argc != 6)
		return (0);
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
		if (pthread_create(threads + i, NULL, philosopher, data_args + i))
			perror_then_exit(PTHREAD_CREATE_ERROR);
		i++;
	}
	check_time_to_die__or__meal_count(data);
	return (0);
}
