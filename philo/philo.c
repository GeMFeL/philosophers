/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:50:11 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/08 12:45:03 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_someone__thread__die(t_data *data)
{
	int		i;
	time_t	curent_time;
	int		all_still_alive;

	all_still_alive = 1;
	if (! data->meal_count)
		return ;
	usleep(1000);
	while (all_still_alive)
	{
		curent_time = get_curent_time_in_msec() - data->date_of_birth;
		i = 0;
		while (i < data->num_of_philo)
		{
			if (curent_time - data->last_meal[i] > data->time_to_die)
			{
				// printf("%7ld: %d died\n", data->last_meal[i] + data->time_to_die, i + 1);
				printf("%7ld: %d died\n", curent_time, i + 1);
				all_still_alive = 0;
			}
			i++;
		}
	}
}

int main(int ac, char **av)
{
	t_data		**data_args;
	t_data		*data;
	pthread_t	*threads;
	int			i;

	if (ac != 5 && ac != 6)
		return 0;
	data_args = initialising_data(av + 1);
	data = data_args[0];
	threads = (pthread_t *)malloc(sizeof(pthread_t) * data->num_of_philo);
	if (! threads)
		perror_then_exit(MALLOC_ERROR);
	i = 0;
	data->date_of_birth = get_curent_time_in_msec();
	while (i < data->num_of_philo)
	{
		pthread_create(threads + i, NULL, philosopher, (data_args + i));
		// usleep(100);
		i++;
	}

	check_someone__thread__die(data);

	return 0;
}
