/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dly <dly@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:49:20 by dly               #+#    #+#             */
/*   Updated: 2023/02/03 18:31:28 by dly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_info	rules;

	if (ac < 5 || ac > 6)
		return (write(2, "Use 5 or 6 args!\n", 18), 1);
	if (init_all(&rules, av))
		return (free(rules.philo), 1);
	simulation(&rules);
	if (simulation(&rules))
		return (end_simulation(&rules), 1);
	end_simulation(&rules);
	return (0);
}
