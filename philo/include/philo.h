/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:48:25 by dly               #+#    #+#             */
/*   Updated: 2023/02/09 18:31:25 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* pthread */
# include <pthread.h>
/* gettimeofday */
# include <sys/time.h>
/* write */
# include <unistd.h>
/* malloc */
# include <stdlib.h>
/* exit */
# include <stdio.h>
/* bool */
# include <stdbool.h>
/* INT_MAX */
# include <limits.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking" 

struct	s_info;

typedef struct s_philo
{
	pthread_t		th;
	int				id;
	int				eat_count;
	long long		last_meal;
	pthread_mutex_t	meal_time;
	// pthread_mutex_t	left_fork;
	// pthread_mutex_t	*right_fork;
	int				left_fork;
	int				right_fork;
	struct s_info	*rules;
	
}		t_philo;

typedef struct s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	long long		start_time;
	bool			end;
	bool			all_eat;
	int				nb_ph_ate;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		th_end;
	pthread_mutex_t	printing;
	pthread_mutex_t	meal;
	pthread_mutex_t	stop;
	pthread_mutex_t	dead;
}		t_info;

/* init.c */
int			init_all(t_info *rules, char **av);

/* free.c */
void		free_all(t_info *rules);

/* utils.c */
int			ft_atoi(const char *nptr);
long long	timestamp(void);
void		ft_usleep(long long time);
void		print_action(t_philo *p, int id, char *str);

/* philo.c */
bool	is_it_stop(t_info *rules);
void		end_simulation(t_info *rules);
int			simulation(t_info *rules);

/* action.c */
int			ft_action(t_philo *p);

#endif