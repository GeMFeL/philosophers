/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:07:05 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/10 18:06:04 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philosopher_routine(t_data *data, pthread_mutex_t *right, \
								pthread_mutex_t *left, int id)
{
	time_t	eat_time;

	usleep(id * 50);
	while (1)
	{
		pthread_mutex_lock(right);
		printf("%7ld: %d has taken a fork\n", get_curent_time_in_msec() - data->date_of_birth, id + 1);
		pthread_mutex_lock(left);
		eat_time = get_curent_time_in_msec() - data->date_of_birth;
		if (data->meal_count < 0)
			data->last_meal[id] = eat_time;
		else
			data->last_meal[id] += 1;
		printf("%7ld: %d is eating\n", eat_time, id + 1);
		exact_sleep_in_msec(data->time_to_eat);
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
		printf("%7ld: %d is sleeping\n", get_curent_time_in_msec() - data->date_of_birth, id + 1);
		exact_sleep_in_msec(data->time_to_sleep);
		printf("%7ld: %d is thinking\n", get_curent_time_in_msec() - data->date_of_birth, id + 1);
	}
}

void	*philosopher(t_data **data_args)
{
	t_data			*data;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	int				id;

	data = *data_args;
	id = ((void *)data_args - data->initial_value_of_data_args) / sizeof(void *);
	right = data->mutexs + id;
	left = data->mutexs + ((id + 1) % data->num_of_philo);
	philosopher_routine(data, right, left, id);
	return NULL;
}
