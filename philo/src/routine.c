/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:36:21 by tordner           #+#    #+#             */
/*   Updated: 2025/05/13 14:56:51 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *monitor_routine(void *arg)
{
	t_data	*data;
	int		i;
	long	time_since_meal;

	data = (t_data *)arg;
	while (1)
	{
		precise_usleep(1000);
		i = -1;
		while (++i < data->num_philosophers)
		{
			time_since_meal = get_time_ms() - data->philos[i].last_meal_time;
			if (time_since_meal > data->time_to_die)
			{
				log_state(&data->philos[i], data->philos[i].id, "died");
				
			}
			// if (check_meal_completion(sim))
			// {
			// 	log_state(0, "All philosophers ate enough");
			// 	exit(0);
			// }
		}
	}
	return (NULL);
}

static void	handle_single_philosopher(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	log_state(philo, philo->id, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	precise_usleep(philo->data->time_to_die * 1000);
	log_state(philo, philo->id, "died");
	return ;
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (get_time_ms() < philo->data->start_time)
		precise_usleep(10);
	if (philo->data->num_philosophers == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	if (philo->id % 2 == 1)
		precise_usleep((philo->data->time_to_eat * 1000) / 2);
	while (1)
	{
		log_state(philo, philo->id, "is thinking");
		precise_usleep(100);
		pthread_mutex_lock(philo->left_fork);
		log_state(philo, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		log_state(philo, philo->id, "has taken a fork");
		log_state(philo, philo->id, "is eating");
		precise_usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		pthread_mutex_lock(philo->data->meal_time);
		philo->last_meal_time = get_time_ms();
		pthread_mutex_unlock(philo->data->meal_time);
		philo->meals_eaten++;

		log_state(philo, philo->id, "is sleeping");
		precise_usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

int	start_table(t_data *data)
{
	pthread_t	monitor;
	int	i;

	i = 0;
	data->start_time = get_time_ms() + 300;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return (1);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
