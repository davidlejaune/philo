/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:36:08 by dly               #+#    #+#             */
/*   Updated: 2023/02/10 21:19:51 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_atoi(char const *nptr)
{
	size_t	i;
	long	res;

	if (!nptr)
		return (0);
	i = 0;
	res = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return (-1);
		res *= 10;
		res += nptr[i] - '0';
		i++;
	}
	return (res);
}

long long	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_action(t_philo *p, int id, char *str)
{
	long long	time;

	sem_wait(p->rules->sem_print);
	time = timestamp() - p->rules->start_time;
	if (time >= 0 && time <= (long long)INT_MAX)
		printf("%lld %d %s\n", timestamp() - p->rules->start_time, id, str);
	sem_post(p->rules->sem_print);
}

void	ft_usleep(long long time)
{
	long long	past;

	past = timestamp();
	while ((timestamp() - past) < time)
		usleep(50);
}
