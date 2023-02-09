/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:10:28 by dly               #+#    #+#             */
/*   Updated: 2023/02/09 20:40:07 by dly              ###   ########.fr       */
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

void	start_sync(long long t_start)
{
	while (timestamp() < t_start)
		// continue ;
		usleep(100);
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
	if (time - p->last_meal >= p->rules->time_to_die)
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
	int	i;
	bool	all_eat;

	i = 0;
	all_eat = true;
	while(i < rules->nb_philo)
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
		// usleep(10);
	}
	
	return (NULL);
}

// void	*routine_check_death(void *rules)
// {
// 	t_philo	*p;

// 	p = (t_philo *)rules;
// 	ft_usleep(p->rules->time_to_die + 1);
// 	pthread_mutex_lock(&p->rules->meal);
// 	if (!is_dead(p, 0) && timestamp() - p->last_meal >= p->rules->time_to_die)
// 	{
// 		pthread_mutex_unlock(&p->rules->meal);
// 		print_action(p, p->id, "died");
// 		is_dead(p, 1);
// 		return (NULL);
// 	}
// 	pthread_mutex_unlock(&p->rules->meal);
// 	return (NULL);
// }
// void	solo_phi(t_philo *p)
// {
// 	pthread_mutex_lock(&p->rules->forks[p->left_fork]);
// 	print_action(p, p->id, "has taken a fork");
// 	ft_usleep(p->rules->time_to_die);
// 	print_action(p, p->id, "died");
// 	pthread_mutex_unlock(&p->rules->forks[p->left_fork]);
// }

void	*routine(void *rules)
{
	t_philo		*p;
	// pthread_t	t;

	p = (t_philo *)rules;
	pthread_mutex_lock(&p->meal_time);
	p->last_meal = p->rules->start_time;
	pthread_mutex_unlock(&p->meal_time);
	start_sync(p->rules->start_time);
	// if (p->rules->nb_philo == 0)
	// {
	// 	solo_phi(p);
	// 	return (NULL);
	// }
	if (!(p->id % 2))
	
	{
		print_action(p, p->id, "is thinking");
		ft_usleep(p->rules->time_to_eat / 100);
		
	}
	while (!is_it_stop(p->rules))
	{
		if (ft_action(p))
			return (NULL);
		// if (p->eat_count == p->rules->max_eat)
		// {
		// 	pthread_mutex_lock(&p->rules->dead);




		// 	p->rules->nb_ph_ate++;
		// 	if (p->rules->nb_ph_ate == p->rules->nb_philo)
		// 		is_dead(p, 1);
		// 	pthread_mutex_unlock(&p->rules->dead);
		// 	break ;
		// }
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
		// pthread_mutex_destroy(&rules->philo[i].left_fork);
		i++;
	}
	if (rules->philo)
		free(rules->philo);
	if (pthread_mutex_destroy(&rules->dead))
		write(2, "error\n", 6);
	if (pthread_mutex_destroy(&rules->printing))
		write(2, "error\n", 6);
	if (pthread_mutex_destroy(&rules->meal))
		write(2, "error\n", 6);
	if (pthread_mutex_destroy(&rules->stop))
		write(2, "error\n", 6);
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
		// if (pthread_mutex_init(&(rules->philo[i].left_fork), NULL))
		// {
		// 	write(2, "lal",3);	
		// 	return (1);
		// }
		// if (i == rules->nb_philo - 1)
		// 	rules->philo[i].right_fork = &rules->philo[0].left_fork;
		// else
		// 	rules->philo[i].right_fork = &rules->philo[i + 1].left_fork;
		if (pthread_create(&rules->philo[i].th, NULL
				, &routine, &rules->philo[i]))
			return (1);
	}
	// if (rules->nb_philo > 1)
	// {
		if (pthread_create(&rules->th_end, NULL
				, &check_death, rules))
			return (1);
	// }

	i = 0;
	while (i < rules->nb_philo)
	{
		if (pthread_join(rules->philo[i].th, NULL))
			return (1);
		i++;
	}
	// if (rules->nb_ph_ate > 1)
	// {
		if (pthread_join(rules->th_end, NULL))
		return (1);
	// }
	return (0);
}
