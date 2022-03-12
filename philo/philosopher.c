/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:07:05 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/12 13:14:26 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philosopher_wait_forks_then_start_eating(t_data *data, int id, \
							pthread_mutex_t *right, pthread_mutex_t *left)
{
	pthread_mutex_lock(right);
	pthread_mutex_lock(data->print_turn);
	printf("%ld: %d has taken a fork\n", get_curent_time_in_msec(), id + 1);
	pthread_mutex_unlock(data->print_turn);
	pthread_mutex_lock(left);
	pthread_mutex_lock(data->print_turn);
	if (data->meal_count < 0)
		data->last_meal[id] = get_curent_time_in_msec();
	printf("%ld: %d is eating\n", get_curent_time_in_msec(), id + 1);
	pthread_mutex_unlock(data->print_turn);
	exact_sleep_in_msec(data->time_to_eat);
	pthread_mutex_unlock(right);
	pthread_mutex_unlock(left);
	if (data->meal_count > 0)
		data->last_meal[id] += 1;
}

void	*philosopher(void *data_args)
{
	t_data			*data;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	int				id;

	data = *(t_data **)data_args;
	id = (data_args - data->initial_value_of_data_args) / sizeof(void *);
	right = data->forks + id;
	left = data->forks + ((id + 1) % data->num_of_philo);
	usleep(id * 50);
	while (1)
	{
		philosopher_wait_forks_then_start_eating(data, id, right, left);
		pthread_mutex_lock(data->print_turn);
		printf("%ld: %d is sleeping\n", get_curent_time_in_msec(), id + 1);
		pthread_mutex_unlock(data->print_turn);
		exact_sleep_in_msec(data->time_to_sleep);
		pthread_mutex_lock(data->print_turn);
		printf("%ld: %d is thinking\n", get_curent_time_in_msec(), id + 1);
		pthread_mutex_unlock(data->print_turn);
	}
	return (NULL);
}
