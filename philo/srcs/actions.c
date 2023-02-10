/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:29:00 by dly               #+#    #+#             */
/*   Updated: 2023/02/10 20:27:14 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_take_fork(t_philo *p)
{
	pthread_mutex_lock(&p->rules->forks[p->left_fork]);
	print_action(p, p->id, "has taken a fork");
	if (p->rules->nb_philo == 1)
	{
		ft_usleep(p->rules->time_to_die + 10);
		return (1);
	}
	pthread_mutex_lock(&p->rules->forks[p->right_fork]);
	print_action(p, p->id, "has taken a fork");
	return (0);
}

static void	ft_eating(t_philo *p)
{
	pthread_mutex_lock(&p->meal_time);
	print_action(p, p->id, "is eating");
	p->last_meal = timestamp();
	pthread_mutex_unlock(&p->meal_time);
	ft_usleep(p->rules->time_to_eat);
	pthread_mutex_lock(&p->meal_time);
	p->eat_count++;
	pthread_mutex_unlock(&p->meal_time);
	pthread_mutex_unlock(&p->rules->forks[p->right_fork]);
	pthread_mutex_unlock(&p->rules->forks[p->left_fork]);
}

static void	ft_sleeping(t_philo *p)
{
	print_action(p, p->id, "is sleeping");
	ft_usleep(p->rules->time_to_sleep);
}

int	ft_action(t_philo *p)
{
	if (ft_take_fork(p))
		return (1);
	ft_eating(p);
	ft_sleeping(p);
	print_action(p, p->id, "is thinking");
	return (0);
}
