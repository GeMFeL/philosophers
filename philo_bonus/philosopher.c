/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:07:05 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/11 12:45:38 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_all_child_procs__philosophers_(t_data *data, int my_id)
{
	pid_t	first_pid;
	int		i;

	first_pid = data->pids[0];
	i = 0;
	while (i < data->num_of_philo)
	{
		if (i != my_id)
		{
			//printf("\nphilo %d have pid %d has killed\n\n", i + 1, data->pids[i]);
			kill(first_pid + i, SIGKILL);
		}
		i++;
	}
}

static void	*check_time_to_die(void *p_data)
{
	t_philo_data	*philo_data;
	time_t			curent_time;

	philo_data = (t_philo_data *)p_data;
	usleep(1000);
	while (1)
	{
		curent_time = get_curent_time_in_msec();
		if (curent_time - philo_data->last_meal >= philo_data->data->time_to_die)
		{
			philo_data->am_die = 1;
			printf("%7ld: %d died\n", curent_time, philo_data->id + 1);
			// kill(0, SIGKILL);
			kill_all_child_procs__philosophers_(philo_data->data, philo_data->id);
			exit (0);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	*check_meal_count(void *p_data)
{
	t_philo_data	*philo_data;

	philo_data = (t_philo_data *)p_data;
	usleep(1000);
	while (1)
	{
		if (philo_data->meal_count >= philo_data->data->meal_count)
			exit (0);
		usleep(1000);
	}
	return NULL;
}

static void	if_am_die_wait_until_exit(t_philo_data *philo_data)
{
	if (philo_data->am_die)
		while (1)
			exact_sleep_in_msec(10);
}

static void	philosopher__start_eating_(t_philo_data *philo_data)
{
	time_t	eat_time;

	eat_time = get_curent_time_in_msec();
	if (philo_data->data->meal_count < 0)
		philo_data->last_meal = eat_time;
	if_am_die_wait_until_exit(philo_data);
	printf("%7ld: %d is eating\n", eat_time, philo_data->id + 1);
	exact_sleep_in_msec(philo_data->data->time_to_eat);
	sem_post(philo_data->data->forks);
	sem_post(philo_data->data->forks);
	if (philo_data->data->meal_count > 0)
		philo_data->meal_count += 1;
}

void	philosopher(t_data *data, int id)
{
	t_philo_data	*philo_data;
	pthread_t		thread_checker[1];

	philo_data = malloc(sizeof(t_philo_data));
	philo_data->id = id;
	philo_data->data = data;
	philo_data->am_die = 0;
	philo_data->meal_count = 0;
	philo_data->last_meal = get_curent_time_in_msec();
	if (data->meal_count < 0)
		pthread_create(thread_checker, NULL, check_time_to_die, philo_data);
	else
		pthread_create(thread_checker, NULL, check_meal_count, philo_data);
	while (1)
	{
		sem_wait(data->forks);
		if_am_die_wait_until_exit(philo_data);
		printf("%7ld: %d has taken a fork\n", get_curent_time_in_msec(), id + 1);
		sem_wait(data->forks);
		philosopher__start_eating_(philo_data);
		if_am_die_wait_until_exit(philo_data);
		printf("%7ld: %d is sleeping\n", get_curent_time_in_msec(), id + 1);
		exact_sleep_in_msec(data->time_to_sleep);
		if_am_die_wait_until_exit(philo_data);
		printf("%7ld: %d is thinking\n", get_curent_time_in_msec(), id + 1);
	}
	exit (0);
}
