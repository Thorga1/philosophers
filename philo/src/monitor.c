/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:48:22 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/17 18:44:26 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_dead(t_data *data, int i)
{
	pthread_mutex_lock(&data->lock);
	if (get_time() - data->philos[i].last_meal > (size_t)data->time_to_die)
	{
		message(&data->philos[i], "died");
		data->dead = 1;
	}
	pthread_mutex_unlock(&data->lock);
	usleep(100);
}

void	death(t_data *data)
{
	int	i;

	while (data->finished != 1 || data->dead != 1)
	{
		i = 0;
		while (i < data->num_philosophers && data->dead != 1)
		{
			is_dead(data, i);
			i++;
		}
		if (data->dead == 1)
			break ;
		i = 0;
		while (data->num_times_must_eat != -1 && data->philos[i].meal_count \
			>= data->num_times_must_eat
			&& i < data->num_philosophers)
			i++;
		if (i == data->num_philosophers)
			data->finished = 1;
	}
}
