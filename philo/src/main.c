/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:36:09 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/01 17:45:34 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_simulation	sim;

	if (parse_arguments(&sim.data, ac, av))
		return (1);
	if (init_simulation(&sim))
		return (1);
	if (start_simulation(&sim))
		return (1);
	cleanup_simulation(&sim);
	return (0);
}
