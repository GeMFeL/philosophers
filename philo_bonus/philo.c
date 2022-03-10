/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:50:11 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/10 21:10:48 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	if (argc != 5 && argc != 6)
		return 0;
	data = initialising_data(argv + 1);
	i = 0;
	while (i < data->num_of_philo)
	{
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			perror_then_exit(FORK_ERROR);
		if (! data->pids[i])
			philosopher(data, i);
		i++;
	}

	i = 0;
	while (i < data->num_of_philo)
	{
		waitpid(data->pids[i], NULL, 0);
		i++;
	}
	sem_unlink(SEM_FORKS_NAME);
	free(data->pids);
	free(data);
	return 0;
}
