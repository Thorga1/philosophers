/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:37:18 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/01 17:45:06 by thorgal          ###   ########.fr       */
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
	int	num_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_must_eat;
}	t_data;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	long			last_meal_time;
}	t_philosopher;

typedef struct s_simulation
{
	t_data			data;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
}	t_simulation;

int		ft_atoi(const char *str);

int		init_forks(t_data *data);
int		parse_arguments(t_data *data, int ac, char **av);
void	log_state(int id, const char *state);
long	get_current_time(void);
void	cleanup_simulation(t_simulation *sim);
void	*philosopher_routine(void *arg);
int		start_simulation(t_simulation *sim);
int		init_simulation(t_simulation *sim);

#endif