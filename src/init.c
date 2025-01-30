/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:50:15 by thorgal           #+#    #+#             */
/*   Updated: 2025/01/30 16:48:17 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arguments(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("Error: Invalid number of argruments\n"), FAILURE);
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -1;
	if (data->num_philos < 1 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (ac == 6 && data->must_eat_count <= 0))
	{
		printf("Error: Invalid arguments\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		printf("Error: Fork allocation failed\n");
		return (FAILURE);
	}
	i = 0;
	while (i < data->num_philos)
	{

	}
}
