/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchakir <jchakir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 16:54:11 by jchakir           #+#    #+#             */
/*   Updated: 2022/03/08 16:25:30 by jchakir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

static int	is_a_integer(char *str)
{
	if (! str || ! *str)
		return (0);
	if (ft_isdigit(*str))
		str++;
	else if ((*str == '-' || *str == '+') && *(str + 1))
		str++;
	else
		return (0);
	while (*str)
	{
		if (! ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	custom_atoi(char *str)
{
	int		sign;
	long	res;

	res = 0;
	sign = 1;
	if (! is_a_integer(str))
		put_error_then_exit(ARG_ERROR);
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str) && res < 2147483648)
		res = res * 10 + *str++ - 48;
	if (res > 2147483647 && sign == 1)
		put_error_then_exit(ARG_ERROR);
	if (res > 2147483648 && sign == -1)
		put_error_then_exit(ARG_ERROR);
	return (sign * (int)res);
}
