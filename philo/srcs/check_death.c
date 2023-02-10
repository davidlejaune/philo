/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:37:01 by dly               #+#    #+#             */
/*   Updated: 2023/02/10 20:41:52 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_it_stop(t_info *rules)
{
	bool	status;

	status = false;
	pthread_mutex_lock(&rules->stop);
	if (rules->end)
		status = true;
	pthread_mutex_unlock(&rules->stop);
	return (status);
}

static void	is_stop(t_info *rules, bool status)
{
	pthread_mutex_lock(&rules->stop);
	rules->end = status;
	pthread_mutex_unlock(&rules->stop);
}

static bool	is_dead(t_philo *p)
{
	long long	time;

	time = timestamp();
	if (time - p->last_meal > p->rules->time_to_die)
	{
		print_action(p, p->id, "died");
		is_stop(p->rules, true);
		pthread_mutex_unlock(&p->meal_time);
		return (true);
	}
	return (false);
}

static bool	end_simu(t_info *rules)
{
	int		i;
	bool	all_eat;

	i = 0;
	all_eat = true;
	while (i < rules->nb_philo)
	{
		pthread_mutex_lock(&rules->philo[i].meal_time);
		if (is_dead(&rules->philo[i]))
			return (true);
		if (rules->max_eat != -1 && rules->philo[i].eat_count < rules->max_eat)
			all_eat = false;
		pthread_mutex_unlock(&rules->philo[i].meal_time);
		i++;
	}
	if (rules->max_eat != -1 && all_eat)
	{
		is_stop(rules, true);
		return (true);
	}
	return (false);
}

void	*check_death(void *data)
{
	t_info	*rules;

	rules = (t_info *)data;
	start_sync(rules->start_time);
	while (1)
	{
		if (end_simu(rules))
			return (NULL);
		usleep(900);
	}
	return (NULL);
}
