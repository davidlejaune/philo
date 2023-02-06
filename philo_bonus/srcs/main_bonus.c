/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:10:15 by dly               #+#    #+#             */
/*   Updated: 2023/02/03 18:43:08 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int ac, char **av)
{
	t_info	rules;

	if (ac < 5 || ac > 6)
		return (write(2, "Use 5 or 6 args!\n", 18), 1);
	if (init_all(&rules, av))
		return (free(rules.philo), 1);
	if (simulation(&rules))
		return (end_simulation(&rules), 1);
	return (0);
}
