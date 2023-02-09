/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:35:04 by dly               #+#    #+#             */
/*   Updated: 2023/02/09 19:36:45 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	init_semaphore(t_info *rules)
{
	sem_unlink("start");
	sem_unlink("print");
	sem_unlink("stop");
	sem_unlink("fork");
	sem_unlink("meal");
	rules->sem_start = sem_open("start", O_CREAT, 0600, 0);
	rules->sem_print = sem_open("print", O_CREAT, 0600, 1);
	rules->sem_stop = sem_open("stop", O_CREAT, 0600, 0);
	rules->sem_fork = sem_open("fork", O_CREAT, 0600, rules->nb_philo);
	rules->sem_meal = sem_open("meal", O_CREAT, 0600, 1);
	if (rules->sem_start == SEM_FAILED || rules->sem_print == SEM_FAILED
		|| rules->sem_stop == SEM_FAILED || rules->sem_fork == SEM_FAILED || rules->sem_meal == SEM_FAILED)
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
		rules->philo[i].rules = rules;
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
	if (init_philo(rules))
		return (1);
	if (init_semaphore(rules))
		return (1);
	return (0);
}
