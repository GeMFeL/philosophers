/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:07:05 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/08 12:45:03 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philosopher_routine(t_data *data, pthread_mutex_t *right, \
								pthread_mutex_t *left, int id)
{
	time_t	eat_time;
	int		meal_count;

	meal_count = data->meal_count;
	usleep(id * 50);
	while (meal_count)
	{
		pthread_mutex_lock(right);
		printf("%7ld: %d has taken a fork\n", get_curent_time_in_msec() - data->date_of_birth, id + 1);
		pthread_mutex_lock(left);
		eat_time = get_curent_time_in_msec() - data->date_of_birth;
		data->last_meal[id] = eat_time;
		printf("%7ld: %d is eating\n", eat_time, id + 1);
		exact_sleep_in_msec(data->time_to_eat);
		pthread_mutex_unlock(right);
		pthread_mutex_unlock(left);
		printf("%7ld: %d is sleeping\n", get_curent_time_in_msec() - data->date_of_birth, id + 1);
		exact_sleep_in_msec(data->time_to_sleep);
		printf("%7ld: %d is thinking\n", get_curent_time_in_msec() - data->date_of_birth, id + 1);
		meal_count--;
	}
}

void	*philosopher(void *data_args)
{
	t_data			*data;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	int				id;

	data = *((t_data **)data_args);
	id = (data_args - data->initial_value_of_data_args) / sizeof(void *);
	right = data->mutexs + id;
	left = data->mutexs + ((id + 1) % data->num_of_philo);
	philosopher_routine(data, right, left, id);
	return NULL;
}
