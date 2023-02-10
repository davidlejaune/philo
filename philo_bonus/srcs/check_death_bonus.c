/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 20:54:07 by dly               #+#    #+#             */
/*   Updated: 2023/02/10 21:01:19 by dly              ###   ########.fr       */
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
		sem_wait(p->rules->sem_meal);
		if (timestamp() - p->last_meal > p->rules->time_to_die)
		{
			sem_post(p->rules->sem_meal);
			print_action(p, p->id, "died");
			ft_end_stop(p->rules);
			break ;
		}
		sem_post(p->rules->sem_meal);
		usleep(900);
	}
	return (NULL);
}

void	init_monitoring(t_philo *p)
{
	pthread_t	t;

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
}
