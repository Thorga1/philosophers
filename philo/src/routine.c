/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:56:33 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/01 18:05:41 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int check_meal_completion(t_simulation *sim)
{
    int i;

	if (sim->data.num_times_must_eat == -1)
		return (0);
	i = 0;
	while (i < sim->data.num_philosophers)
	{
		if (sim->philosophers[i].meals_eaten < sim->data.num_times_must_eat)
			return (0);
		i++;
	}
	return (1);
}

static void *monitor_routine(void *arg)
{
	t_simulation	*sim;
	int				i;
	long			time_since_meal;

	sim = (t_simulation *)arg;
	while (1)
	{
		usleep(1000);
		i = -1;
		while (++i < sim->data.num_philosophers)
		{
			// Check starvation
			time_since_meal = get_current_time() - sim->philosophers[i].last_meal_time;
			if (time_since_meal > sim->data.time_to_die)
			{
				log_state(sim->philosophers[i].id, "died");
				exit(0);  // Terminate the entire program
			}
			if (check_meal_completion(sim))
			{
				log_state(0, "All philosophers ate enough");
				exit(0);
			}
		}
	}

	return (NULL);
}

static void	handle_single_philosopher(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	log_state(philo->id, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	log_state(philo->id, "died");
	return ;
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	philo = (t_philosopher *)arg;
	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	data = philo->data;
	if (philo->data->num_philosophers == 1)
	{
		handle_single_philosopher(philo);
		return (NULL);
	}
	while (1)
	{
		log_state(philo->id, "is thinking");
		usleep(data->time_to_eat * 1000);

		if (philo->id % 2 == 0)
		{
			first_fork = philo->right_fork;
			second_fork = philo->left_fork;
		}
		pthread_mutex_lock(first_fork);
		log_state(philo->id, "has taken a fork");
		pthread_mutex_lock(second_fork);
		log_state(philo->id, "has taken a fork");

		log_state(philo->id, "is eating");
		philo->last_meal_time = get_current_time();
		philo->meals_eaten++;
		usleep(data->time_to_eat * 1000);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		log_state(philo->id, "is sleeping");
		usleep(data->time_to_sleep * 1000);
	}
	return (NULL);
}

int	start_simulation(t_simulation *sim)
{
    pthread_t monitor;
    int i;

    i = 0;
    while (i < sim->data.num_philosophers)
	{
        sim->philosophers[i].last_meal_time = get_current_time();
		i++;
	}
    i = 0;
    while (i < sim->data.num_philosophers) {
        if (pthread_create(&sim->philosophers[i].thread, NULL, 
                          philosopher_routine, &sim->philosophers[i]) != 0) {
            printf("Error: Thread creation failed.\n");
            return (1);
        }
		pthread_detach(sim->philosophers[i].thread);
		i++;
    }
    if (pthread_create(&monitor, NULL, monitor_routine, sim) != 0) {
        printf("Error: Monitor thread creation failed.\n");
        return (1);
    }
    pthread_join(monitor, NULL);
    return (0);
}