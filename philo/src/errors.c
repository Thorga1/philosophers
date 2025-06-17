/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:45:17 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/17 18:44:52 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_numbers(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_error(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_"
			"to_sleep [number_of_times_each_philosopher_must_eat]\n", av[0]);
		return (1);
	}
	if (check_numbers(ac, av) == 1)
		return (printf("Arguments have to be digits only\n"), 1);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		return \
		(printf("Number of philosopher has to be between 1 and 200\n"), 1);
	return (0);
}
