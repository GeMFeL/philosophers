/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:49:19 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/12 13:24:52 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
// # include <strings.h>
# include <signal.h>

# define SEM_FORKS_NAME "PhILOsopHERsFoRKs"
# define SEM_PRINT_TURN_NAME "PhILOsopHERsPRinTtuRN"
# define SEM_ERROR "can't create semaphore: allready exist"
# define ARG_ERROR "argument not a number"
# define ARG_VALUE_ERROR "Arguments should be non negative or zero"
# define MALLOC_ERROR "malloc() error"
# define FORK_ERROR "fork() error"
# define THREAD_ERROR "pthread_create() error"

typedef struct s_data
{
	int		num_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		meal_count;
	pid_t	*pids;
	sem_t	*forks;
	sem_t	*print_turn;
}	t_data;

typedef struct s_philo_data
{
	int		id;
	int		meal_count;
	time_t	last_meal;
	t_data	*data;
}	t_philo_data;

void	put_error_then_exit(const char *str);
void	perror_then_exit(const char *str);
int		custom_atoi(char *str);
time_t	get_curent_time_in_msec(void);
void	exact_sleep_in_msec(int msec);
t_data	*initialising_data(char *argv[]);
void	philosopher(t_data *data, int id);

#endif
