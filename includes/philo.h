/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:37:18 by thorgal           #+#    #+#             */
/*   Updated: 2025/01/30 15:44:21 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# define SUCCESS 0
# define FAILURE 1

typedef struct s_data
{
	int				num_philos;       // Number of philosophers
	int				time_to_die;      // Time before a philosopher dies (ms)
	int				time_to_eat;      // Time a philosopher takes to eat (ms)
	int				time_to_sleep;    // Time a philosopher sleeps (ms)
	int				must_eat_count;   // Optional: Number of times each philosopher must eat
	long			start_time;       // Simulation start timestamp (ms)
	bool			simulation_end;   // Flag to check if simulation should stop

	pthread_mutex_t	*forks;           // Array of mutexes for forks
	pthread_mutex_t	log_mutex;        // Mutex for writing logs
	struct s_philo	*philos;          // Array of philosopher structs
}	t_data;

typedef struct s_philo
{
	int				id;               // Philosopher ID (1 to num_philos)
	int				meals_eaten;      // Number of meals eaten
	long			last_meal_time;   // Timestamp of last meal (ms)
	pthread_t		thread;           // Thread handling this philosopher
	t_data			*data;            // Pointer to shared data
	pthread_mutex_t	*left_fork;       // Pointer to left fork mutex
	pthread_mutex_t	*right_fork;      // Pointer to right fork mutex
}	t_philo;

int		ft_atoi(const char *str);

int		init_simulation(t_data *data, int argc, char **argv);
int		init_philosophers(t_data *data);
int		init_forks(t_data *data);

void	*philosopher_routine(void *philo_struct);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);

void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);

long	get_current_time(void);

void	log_status(int id, char *status, t_data *data);

void	free_resources(t_data *data);

#endif