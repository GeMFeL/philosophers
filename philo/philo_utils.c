/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:18:29 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/12 13:16:37 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_curent_time_in_msec(void)
{
	struct timeval	curent_time;
	time_t			time;

	gettimeofday(&curent_time, NULL);
	time = curent_time.tv_sec * 1000 + curent_time.tv_usec / 1000;
	return (time);
}

void	exact_sleep_in_msec(int msec)
{
	time_t	start;

	start = get_curent_time_in_msec();
	while (get_curent_time_in_msec() - start < msec)
	{
		usleep(500);
	}
}

static void	initialising_data_int_with_atoi(t_data *data, char *argv[])
{
	data->num_of_philo = custom_atoi(argv[0]);
	data->time_to_die = custom_atoi(argv[1]);
	data->time_to_eat = custom_atoi(argv[2]);
	data->time_to_sleep = custom_atoi(argv[3]);
	if (data->num_of_philo <= 0 || data->time_to_die <= 0)
		put_error_then_exit(ARG_VALUE_ERROR);
	if (data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		put_error_then_exit(ARG_VALUE_ERROR);
	data->meal_count = -1;
	if (argv[4])
	{
		data->meal_count = custom_atoi(argv[4]);
		if (data->meal_count <= 0)
			put_error_then_exit(ARG_VALUE_ERROR);
	}
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
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	data->print_turn = malloc(sizeof(pthread_mutex_t));
	data->last_meal = malloc(sizeof(time_t) * data->num_of_philo);
	data_args = malloc(sizeof(t_data *) * data->num_of_philo);
	if (!data->forks || !data->last_meal || !data_args || !data->print_turn)
		perror_then_exit(MALLOC_ERROR);
	data->initial_value_of_data_args = (void *)data_args;
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(data->forks + i, NULL))
			perror_then_exit(MUTEX_ERROR);
		data_args[i++] = data;
	}
	if (pthread_mutex_init(data->print_turn, NULL))
		perror_then_exit(MUTEX_ERROR);
	return (data_args);
}
