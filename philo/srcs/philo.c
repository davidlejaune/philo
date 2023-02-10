/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:10:28 by dly               #+#    #+#             */
/*   Updated: 2023/02/10 20:38:02 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *rules)
{
	t_philo		*p;

	p = (t_philo *)rules;
	pthread_mutex_lock(&p->meal_time);
	p->last_meal = p->rules->start_time;
	pthread_mutex_unlock(&p->meal_time);
	start_sync(p->rules->start_time);
	if (!(p->id % 2))
	{
		print_action(p, p->id, "is thinking");
		ft_usleep(p->rules->time_to_eat / 10);
	}
	while (!is_it_stop(p->rules))
	{
		if (ft_action(p))
			return (NULL);
	}
	return (NULL);
}

void	end_simulation(t_info *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		pthread_mutex_destroy(&rules->philo[i].meal_time);
		i++;
	}
	if (rules->philo)
		free(rules->philo);
	if (rules->forks)
		free(rules->forks);
	if (pthread_mutex_destroy(&rules->dead))
		write(2, "error\n", 6);
	if (pthread_mutex_destroy(&rules->printing))
		write(2, "error\n", 6);
	if (pthread_mutex_destroy(&rules->meal))
		write(2, "error\n", 6);
	if (pthread_mutex_destroy(&rules->stop))
		write(2, "error\n", 6);
}

int	join_thread(t_info *rules)
{
	int	i;

	i = 0;
	if (pthread_create(&rules->th_end, NULL, &check_death, rules))
		return (1);
	while (i < rules->nb_philo)
	{
		if (pthread_join(rules->philo[i].th, NULL))
			return (1);
		i++;
	}
	if (pthread_join(rules->th_end, NULL))
		return (1);
	return (0);
}

int	simulation(t_info *rules)
{
	int	i;

	i = -1;
	rules->start_time = timestamp() + (rules->nb_philo * 20);
	while (++i < rules->nb_philo)
	{
		if (pthread_mutex_init(&(rules->philo[i].meal_time), NULL))
		{
			write(2, "error", 5);
			return (1);
		}
		if (pthread_create(&rules->philo[i].th, NULL
				, &routine, &rules->philo[i]))
			return (1);
	}
	if (join_thread(rules))
		return (1);
	return (0);
}
