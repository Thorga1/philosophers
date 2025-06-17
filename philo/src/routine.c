/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:47:33 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/17 18:38:00 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&philo->fork);
	message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->left_fork->fork);
	message(philo, "has taken a fork");
	pthread_mutex_lock(&data->lock);
	philo->meal_count++;
	message(philo, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->lock);
	my_sleep(data, data->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	handle_single_philo(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	message(philo, "has taken a fork");
	my_sleep(data, data->time_to_die);
	message(philo, "died");
	pthread_mutex_unlock(&philo->fork);
	data->dead = 1;
}

void	*routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->data->num_philosophers == 1)
	{
		handle_single_philo(data, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (data->finished != 1 && data->dead != 1)
	{
		eat(philo);
		message(philo, "is sleeping");
		my_sleep(data, data->time_to_sleep);
		message(philo, "is thinking");
	}
	return (NULL);
}

int	start_table(t_data *data, pthread_t *philo_threads)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&philo_threads[i], NULL, &routine, &data->philos[i]))
		{
			free(philo_threads);
			free(data->philos);
			return (printf("Thread creation failed\n"), 1);
		}
		pthread_mutex_lock(&data->lock);
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->lock);
		i++;
	}
	return (0);
}
