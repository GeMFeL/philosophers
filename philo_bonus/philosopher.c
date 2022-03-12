/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:07:05 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/12 13:24:18 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*check_time_to_die(void *p_data)
{
	t_philo_data	*philo_data;
	time_t			curent_time;

	philo_data = (t_philo_data *)p_data;
	usleep(1000);
	while (1)
	{
		curent_time = get_curent_time_in_msec();
		if (curent_time - philo_data->last_meal > philo_data->data->time_to_die)
		{
			sem_wait(philo_data->data->print_turn);
			printf("%ld: %d died\n", curent_time, philo_data->id + 1);
			free(philo_data);
			exit (0);
		}
		usleep(500);
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
		{
			free(philo_data);
			exit (0);
		}
		usleep(500);
	}
	return (NULL);
}

static void	philosopher_wait_forks_then_eat(t_philo_data *philo_data)
{
	sem_wait(philo_data->data->forks);
	sem_wait(philo_data->data->print_turn);
	printf("%ld: %d has taken a fork\n", get_curent_time_in_msec(), \
											philo_data->id + 1);
	sem_post(philo_data->data->print_turn);
	sem_wait(philo_data->data->forks);
	if (philo_data->data->meal_count < 0)
		philo_data->last_meal = get_curent_time_in_msec();
	sem_wait(philo_data->data->print_turn);
	printf("%ld: %d is eating\n", get_curent_time_in_msec(), \
										philo_data->id + 1);
	sem_post(philo_data->data->print_turn);
	exact_sleep_in_msec(philo_data->data->time_to_eat);
	sem_post(philo_data->data->forks);
	sem_post(philo_data->data->forks);
	if (philo_data->data->meal_count > 0)
		philo_data->meal_count += 1;
}

static void	philosopher_routine(t_philo_data *philo_data)
{
	while (1)
	{
		philosopher_wait_forks_then_eat(philo_data);
		sem_wait(philo_data->data->print_turn);
		printf("%ld: %d is sleeping\n", get_curent_time_in_msec(), \
											philo_data->id + 1);
		sem_post(philo_data->data->print_turn);
		exact_sleep_in_msec(philo_data->data->time_to_sleep);
		sem_wait(philo_data->data->print_turn);
		printf("%ld: %d is thinking\n", get_curent_time_in_msec(), \
											philo_data->id + 1);
		sem_post(philo_data->data->print_turn);
	}
}

void	philosopher(t_data *data, int id)
{
	t_philo_data	*philo_data;
	pthread_t		thread_checker[1];

	philo_data = malloc(sizeof(t_philo_data));
	if (! philo_data)
		perror_then_exit(MALLOC_ERROR);
	philo_data->id = id;
	philo_data->data = data;
	philo_data->meal_count = 0;
	philo_data->last_meal = get_curent_time_in_msec();
	if (data->meal_count < 0)
	{
		if (pthread_create(thread_checker, NULL, check_time_to_die, philo_data))
			perror_then_exit(THREAD_ERROR);
	}
	else
	{
		if (pthread_create(thread_checker, NULL, check_meal_count, philo_data))
			perror_then_exit(THREAD_ERROR);
	}
	philosopher_routine(philo_data);
	exit (0);
}
