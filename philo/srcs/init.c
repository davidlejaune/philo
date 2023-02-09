/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:35:04 by dly               #+#    #+#             */
/*   Updated: 2023/02/09 18:34:19 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_info *rules)
{
	int	i;
	
	i = 0;
	rules->forks = malloc(rules->nb_philo * sizeof(pthread_mutex_t));
	if (!rules->forks)
		return (1);
	while (i < rules->nb_philo)
	{
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&rules->dead, NULL))
		return (1);
	if (pthread_mutex_init(&rules->printing, NULL))
		return (1);
	if (pthread_mutex_init(&rules->meal, NULL))
		return (1);
	if (pthread_mutex_init(&rules->stop, NULL))
		return (1);
	return (0);
}

int	init_philo(t_info *rules)
{
	int	i;

	i = 0;
	rules->philo = malloc(rules->nb_philo * sizeof(t_philo));
	if (!rules->philo)
		return (1);
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].eat_count = 0;
		rules->philo[i].last_meal = 0;
		// rules->philo[i].right_fork = NULL;
		rules->philo[i].left_fork = i;
		rules->philo[i].right_fork = (i + 1) % rules->nb_philo;
		if (!(rules->philo[i].id % 2))
		{
			rules->philo[i].left_fork = (i + 1) % rules->nb_philo;
			rules->philo[i].right_fork = i;
		}
		rules->philo[i].rules = rules;
		rules->philo[i].last_meal = timestamp();
		i++;
	}
	return (0);
}

int	init_all(t_info *rules, char **av)
{
	rules->nb_philo = ft_atoi(av[1]);
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	if (rules-> nb_philo < 1 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0)
		return (1);
	if (av[5])
	{
		rules->max_eat = ft_atoi(av[5]);
		if (rules->max_eat < 0)
			return (1);
	}
	else
		rules->max_eat = -1;
	rules->start_time = timestamp();
	rules->end = false;
	rules->all_eat = false;
	rules->nb_ph_ate = 0;
	if (init_philo(rules))
		return (1);
	if (init_mutex(rules))
		return (1);
	return (0);
}
