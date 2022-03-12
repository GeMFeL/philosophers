/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:49:19 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/12 13:15:44 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

# define ARG_ERROR "argument not a number"
# define ARG_VALUE_ERROR "Arguments should be non negative or zero"
# define MALLOC_ERROR "malloc() error"
# define MUTEX_ERROR "pthread_mutex_init() error"
# define PTHREAD_CREATE_ERROR "pthread_create() error"

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_count;
	time_t			*last_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_turn;
	void			*initial_value_of_data_args;
}					t_data;

void	put_error_then_exit(const char *str);
void	perror_then_exit(const char *str);
int		custom_atoi(char *str);
time_t	get_curent_time_in_msec(void);
void	exact_sleep_in_msec(int msec);
t_data	**initialising_data(char *argv[]);
void	*philosopher(void *data_args);

#endif
