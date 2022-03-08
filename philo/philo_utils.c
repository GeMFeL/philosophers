/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:18:29 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/08 13:44:24 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_curent_time_in_msec(void)
{
	struct timeval	curent_time;
	time_t			time;

	gettimeofday(&curent_time, NULL);
	time = curent_time.tv_sec * 1000 + curent_time.tv_usec / 1000;
	return (time + 1);
}

void	exact_sleep_in_msec(int msec)
{
	time_t	start;

	start = get_curent_time_in_msec();
	while (get_curent_time_in_msec() - start < msec)
	{
		usleep(1000);
	}
}

static void	initialising_data_int_with_atoi(t_data *data, char *argv[])
{
	data->num_of_philo = custom_atoi(argv[0]);
	data->time_to_die = custom_atoi(argv[1]);
	data->time_to_eat = custom_atoi(argv[2]);
	data->time_to_sleep = custom_atoi(argv[3]);
	data->meal_count = -1;
	if (argv[4])
		data->meal_count = custom_atoi(argv[4]);
}

t_data	**initialising_data(char	*argv[])
{
	t_data	*data;
	t_data	**data_args;
	int		i;

	data = malloc(sizeof(t_data));
	if (! data)
		perror_then_exit(MALLOC_ERROR);
	initialising_data_int_with_atoi(data, argv);
	data->mutexs = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	data->last_meal = malloc(sizeof(time_t) * data->num_of_philo);
	data_args = malloc(sizeof(t_data *) * data->num_of_philo);
	if (! data->mutexs || ! data->last_meal || ! data_args)
		perror_then_exit(MALLOC_ERROR);
	data->initial_value_of_data_args = (void *)data_args;
	i = 0;
	while (i < data->num_of_philo)
	{
		data->last_meal[i] = 0;
		pthread_mutex_init(data->mutexs + i, NULL);
		data_args[i] = data;
		i++;
	}
	return (data_args);
}