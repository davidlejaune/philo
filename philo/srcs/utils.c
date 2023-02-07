/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:36:08 by dly               #+#    #+#             */
/*   Updated: 2023/02/03 18:31:41 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

	pthread_mutex_lock(&p->rules->printing);
	time = timestamp() - p->rules->start_time;
	if (!p->rules->end && time >= 0 && time <= (long long)INT_MAX
		&& !is_dead(p, 0))
		printf("%lld %d %s\n", timestamp() - p->rules->start_time, id, str);
	pthread_mutex_unlock(&p->rules->printing);
}

void	ft_usleep(long long time)
{
	long long	past;

	past = timestamp();
	while ((timestamp() - past) < time)
		usleep(time / 10);
}

int	is_dead(t_philo *p, int nb)
{
	pthread_mutex_lock(&p->rules->stop);
	if (nb)
		p->rules->end = true;
	pthread_mutex_unlock(&p->rules->stop);
	pthread_mutex_lock(&p->rules->stop);
	if (p->rules->end)
	{
		pthread_mutex_unlock(&p->rules->stop);
		return (1);
	}
	pthread_mutex_unlock(&p->rules->stop);
	return (0);
}
