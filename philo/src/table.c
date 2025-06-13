/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:04:45 by tordner           #+#    #+#             */
/*   Updated: 2025/05/13 14:49:55 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % \
			data->num_philosophers];
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return ;
}

int	init_table(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
		return (1);
	data->write = malloc(sizeof(pthread_mutex_t));
	if (!data->write)
		return (-1);
	data->death = malloc(sizeof(pthread_mutex_t));
	if (!data->death)
		return (-1);
	data->meal_time = malloc(sizeof(pthread_mutex_t));
	if (!data->meal_time)
		return (-1);
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		 i++;
	}
	if (pthread_mutex_init(data->write, NULL) != 0)
		return (1);
	init_philos(data);
	return (0);
}
