/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:43:02 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/17 18:37:37 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_exit(t_data *data, pthread_t *philo_threads)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
		pthread_join(philo_threads[i++], NULL);
	i = 0;
	while (i < data->num_philosophers)
		pthread_mutex_destroy(&data->philos[i++].fork);
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	free(data->philos);
	free(data);
	free(philo_threads);
}

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*philo_threads;

	if (check_error(ac, av) != 0)
		return (1);
	data = setup_data(ac, av);
	philo_threads = malloc(sizeof(pthread_t) * data->num_philosophers);
	if (start_table(data, philo_threads) == 1)
		return (1);
	death(data);
	free_exit(data, philo_threads);
	return (0);
}
