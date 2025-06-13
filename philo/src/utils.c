/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:36:25 by thorgal           #+#    #+#             */
/*   Updated: 2025/05/13 14:50:22 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	return ((int)res);
}

int	parse_arguments(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_"
			"to_sleep [number_of_times_each_philosopher_must_eat]\n", av[0]);
		return (1);
	}
	data->num_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_times_must_eat = ft_atoi(av[5]);
	else
		data->num_times_must_eat = -1;
	if (data->num_philosophers <= 0
		|| data->time_to_die <= 0
		|| data->time_to_eat <= 0
		|| data->time_to_sleep <= 0
		|| (ac == 6 && data->num_times_must_eat <= 0))
	{
		printf("All arguments must be positive integers.\n");
		return (1);
	}
	return (0);
}

void	cleanup_simulation(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
		free(data->philos);
	if (data->forks)
	{
		while (i < data->num_philosophers)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->write)
		pthread_mutex_destroy(data->write);
	if (data->death)
		pthread_mutex_destroy(data->death);
	if (data->meal_time)
		pthread_mutex_destroy(data->meal_time);
	free(data->meal_time);
	free(data->death);
	free(data->write);
	free(data);
	return ;
}

void	log_state(t_philosopher *philo, int id, const char *state)
{
	pthread_mutex_lock(philo->data->write);
	printf("%ld %d %s\n", get_time_ms() - philo->data->start_time, id, state);
	pthread_mutex_unlock(philo->data->write);
}
