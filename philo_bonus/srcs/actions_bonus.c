/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:29:00 by dly               #+#    #+#             */
/*   Updated: 2023/02/10 19:07:51 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_take_fork(t_philo *p)
{
	sem_wait(p->rules->sem_fork);
	print_action(p, p->id, "has taken a fork");
	sem_wait(p->rules->sem_fork);
	print_action(p, p->id, "has taken a fork");
}

void	ft_eating(t_philo *p)
{
	print_action(p, p->id, "is eating");
	sem_wait(p->rules->sem_meal);
	p->last_meal = timestamp();
	sem_post(p->rules->sem_meal);
	ft_usleep(p->rules->time_to_eat);
	p->eat_count++;
	sem_post(p->rules->sem_fork);
	sem_post(p->rules->sem_fork);
}

void	ft_sleeping(t_philo *p)
{
	print_action(p, p->id, "is sleeping");
	ft_usleep(p->rules->time_to_sleep);
}
