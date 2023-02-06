/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:10:28 by dly               #+#    #+#             */
/*   Updated: 2023/02/06 18:36:42 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine_check_death(void *rules)
{
	t_philo	*p;

	p = (t_philo *)rules;
	ft_usleep(p->rules->time_to_die + 1);
	if (!is_dead(p, 0) && timestamp() - p->last_meal >= p->rules->time_to_die)
	{
		print_action(p, p->id, "died");
		is_dead(p, 1);
		return (NULL);
	}
	return (NULL);
}

void	*routine(void *rules)
{
	t_philo		*p;
	pthread_t	t;

	p = (t_philo *)rules;
	p->last_meal = timestamp();
	if (!(p->id % 2))
		ft_usleep(p->rules->time_to_eat / 10);
	while (!is_dead(p, 0))
	{
		if (pthread_create(&t, NULL, routine_check_death, rules))
			return (NULL);
		// if (pthread_detach(t))
			// return (NULL);
		if (ft_action(p))
			return (NULL);
		if (p->eat_count == p->rules->max_eat)
		{
			p->rules->nb_ph_ate++;
			if (p->rules->nb_ph_ate == p->rules->nb_philo)
				is_dead(p, 1);
			break ;
		}
	}
	return (NULL);
}

void	end_simulation(t_info *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&rules->philo[i].left_fork);
		i++;
	}
	if (rules->philo)
		free(rules->philo);
	pthread_mutex_destroy(&rules->printing);
	pthread_mutex_destroy(&rules->meal);
	pthread_mutex_destroy(&rules->stop);
}

int	simulation(t_info *rules)
{
	int	i;

	i = -1;
	while (++i < rules->nb_philo)
	{
		if (pthread_mutex_init(&(rules->philo[i].left_fork), NULL))
			return (1);
		if (i == rules->nb_philo - 1)
			rules->philo[i].right_fork = &rules->philo[0].left_fork;
		else
			rules->philo[i].right_fork = &rules->philo[i + 1].left_fork;
		if (pthread_create(&rules->philo[i].th, NULL
				, &routine, &rules->philo[i]))
			return (1);
	}
	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_join(rules->philo[i].th, NULL))
			return (1);
		i++;
	}
	return (0);
}
