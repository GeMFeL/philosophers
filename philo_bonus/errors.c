/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 20:47:29 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/04 21:40:45 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putendl_fd(const char *s, int fd)
{
	if (! s)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}

void	put_error_then_exit(const char *str)
{
	ft_putendl_fd(str, 2);
	exit (EXIT_FAILURE);
}

void	perror_then_exit(const char *str)
{
	perror(str);
	exit (EXIT_FAILURE);
}
