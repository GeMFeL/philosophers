/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:18:29 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/12 12:39:29 by jchakir          ###   ########.fr       */
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
		usleep(500);
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

t_data	*initialising_data(char	*argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (! data)
		perror_then_exit(MALLOC_ERROR);
	initialising_data_int_with_atoi(data, argv);
	data->pids = malloc(sizeof(pid_t) * data->num_of_philo);
	if (! data->pids)
		perror_then_exit(MALLOC_ERROR);
	sem_unlink(SEM_FORKS_NAME);
	sem_unlink(SEM_PRINT_TURN_NAME);
	data->forks = sem_open(SEM_FORKS_NAME, O_CREAT, 0666, data->num_of_philo);
	data->print_turn = sem_open(SEM_PRINT_TURN_NAME, O_CREAT, 0666, 1);
	if (data->forks == SEM_FAILED || data->print_turn == SEM_FAILED)
		perror_then_exit(SEM_ERROR);
	return (data);
}
