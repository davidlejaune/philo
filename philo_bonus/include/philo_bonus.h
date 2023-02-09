/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:48:25 by dly               #+#    #+#             */
/*   Updated: 2023/02/09 19:34:17 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

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
// # include <time.h>
/* bool */
# include <stdbool.h>
/* INT_MAX */
# include <limits.h>
/* fork*/
# include <sys/types.h>
/* semaphore */
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
/* waitpid */
# include <sys/types.h>
# include <sys/wait.h>
/* kill */
# include <signal.h>

struct	s_info;

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	int				eat_count;
	long long		last_meal;
	struct s_info	*rules;
}		t_philo;

typedef struct s_info
{
	sem_t			*sem_start;
	sem_t			*sem_print;
	sem_t			*sem_stop;
	sem_t			*sem_fork;
	sem_t			*sem_meal;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	long long		start_time;
	t_philo			*philo;
}		t_info;

/* init.c */
int			init_all(t_info *rules, char **av);

/* utils.c */
int			ft_atoi(char const *nptr);
long long	timestamp(void);
void		ft_usleep(long long time);
void		print_action(t_philo *p, int id, char *str);

/* philo.c */
int			simulation(t_info *rules);
int			end_simulation(t_info *rules);

/* action.c */
void		ft_take_fork(t_philo *p);
void		ft_eating(t_philo *p);
void		ft_sleeping(t_philo *p);

#endif