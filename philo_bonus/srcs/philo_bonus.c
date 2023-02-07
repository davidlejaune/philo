/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:10:28 by dly               #+#    #+#             */
/*   Updated: 2023/02/03 18:43:15 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_end_stop(t_info *rules)
{
	int	i;

	i = 0;
	while (i++ < rules->nb_philo)
		sem_post(rules->sem_stop);
	return (0);
}

void	*check_death(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		if (timestamp() - p->last_meal > p->rules->time_to_die)
		{
			print_action(p, p->id, "died");
			ft_end_stop(p->rules);
			break ;
		}
	}
	return (NULL);
}

void	routine(t_philo *p)
{
	pthread_t	t;

	sem_wait(p->rules->sem_start);
	p->last_meal = timestamp();
	if (pthread_create(&t, NULL, check_death, p) != 0)
	{
		ft_end_stop(p->rules);
		exit(EXIT_FAILURE);
	}	
	if (pthread_detach(t))
	{
		ft_end_stop(p->rules);
		exit(EXIT_FAILURE);
	}	
	if (!(p->id % 2))
		ft_usleep(p->rules->time_to_eat / 10);
	while (p->eat_count != p->rules->max_eat)
	{
		ft_take_fork(p);
		ft_eating(p);
		ft_sleeping(p);
		print_action(p, p->id, "is thinking");
	}
	sem_post(p->rules->sem_stop);
	exit(EXIT_SUCCESS);
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
	if (rules->philo)
		free(rules->philo);
	sem_close(rules->sem_start);
	sem_close(rules->sem_print);
	sem_close(rules->sem_stop);
	sem_close(rules->sem_fork);
	sem_unlink("start");
	sem_unlink("print");
	sem_unlink("stop");
	sem_unlink("fork");
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
