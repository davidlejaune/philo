/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:10:28 by dly               #+#    #+#             */
/*   Updated: 2023/02/10 21:00:12 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	routine(t_philo *p)
{
	sem_wait(p->rules->sem_start);
	p->last_meal = p->rules->start_time;
	init_monitoring(p);
	if (!(p->id % 2))
	{
		print_action(p, p->id, "is thinking");
		ft_usleep(p->rules->time_to_eat / 10);
	}
	while (1)
	{
		ft_take_fork(p);
		ft_eating(p);
		ft_sleeping(p);
		print_action(p, p->id, "is thinking");
		if (p->eat_count == p->rules->max_eat)
			sem_post(p->rules->sem_stop);
	}
	exit(EXIT_SUCCESS);
}

void	free_sem(t_info *rules)
{
	if (rules->philo)
		free(rules->philo);
	sem_close(rules->sem_start);
	sem_close(rules->sem_print);
	sem_close(rules->sem_stop);
	sem_close(rules->sem_fork);
	sem_close(rules->sem_meal);
	sem_unlink("/start");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/fork");
	sem_unlink("/meal");
}

void	kill_process(t_info *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		kill(rules->philo[i].pid, SIGKILL);
		i++;
	}
}

int	end_simulation(t_info *rules)
{
	int	i;

	i = 0;
	while (i++ < rules->nb_philo)
		sem_wait(rules->sem_stop);
	i = 0;
	while (i < rules->nb_philo)
	{
		kill(rules->philo[i].pid, SIGKILL);
		i++;
	}
	i = 0;
	free_sem(rules);
	return (1);
}

int	simulation(t_info *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		rules->philo[i].pid = fork();
		if (rules->philo[i].pid == 0)
			routine(&rules->philo[i]);
		if (rules->philo[i].pid < 0)
			return (ft_end_stop(rules), 1);
		i++;
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		sem_post(rules->sem_start);
		i++;
	}
	end_simulation(rules);
	return (0);
}
