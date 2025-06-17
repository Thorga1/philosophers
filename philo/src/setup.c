/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:45:04 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/17 18:45:07 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
		pthread_mutex_init(&data->philos[i++].fork, NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		if (i == 0)
			data->philos[i].right_fork = \
			&data->philos[data->num_philosophers - 1];
		else
			data->philos[i].right_fork = &data->philos[i - 1];
		if (i + 1 == data->num_philosophers)
			data->philos[i].left_fork = &data->philos[0];
		else
			data->philos[i].left_fork = &data->philos[i + 1];
		i++;
	}
}

void	setup_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meal_count = 0;
		i++;
	}
}

t_data	*setup_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->num_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->dead = 0;
	data->finished = 0;
	data->start_time = get_time();
	if (ac == 6)
		data->num_times_must_eat = ft_atoi(av[5]);
	else
		data->num_times_must_eat = -1;
	data->philos = malloc(sizeof(t_philo) * data->num_philosophers);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->lock, NULL);
	setup_philo(data);
	setup_forks(data);
	return (data);
}
