/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:51:18 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/01 17:54:20 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_sim_philo(t_simulation *sim, int i)
{
	while (i < sim->data.num_philosophers)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].left_fork = &sim->forks[i];
		sim->philosophers[i].right_fork = &sim->forks[(i + 1) % sim ->data.num_philosophers];
		sim->philosophers[i].data = &sim->data;
		sim->philosophers[i].last_meal_time = get_current_time();
		sim->philosophers[i].meals_eaten = 0;
		i++;
	}
	return ;
}

int	init_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	// Allocate forks (mutexes)
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->data.num_philosophers);
	if (!sim->forks)
	{
		printf("Error: Fork allocation failed.\n");
		return (1);
	}
	sim->philosophers = malloc(sizeof(t_philosopher) * sim->data.num_philosophers);
    if (!sim->philosophers) {
        printf("Error: Philosopher allocation failed.\n");
        free(sim->forks);  // Clean up forks if philosopher allocation fails
        return (1);
    }
	// Initialize forks
	while (i < sim->data.num_philosophers)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			printf("Error: Fork mutex init failed.\n");
            free(sim->forks);
            free(sim->philosophers);
			return (1);
		}
		i++;
	}
	i = 0;
	init_sim_philo(sim, i);
	return (0);
}

void	cleanup_simulation(t_simulation *sim)
{
	int i;
	i = 0;
	// Destroy mutexes
	while (i < sim->data.num_philosophers)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	// Free memory
	free(sim->forks);
	free(sim->philosophers);
	return ;
}
