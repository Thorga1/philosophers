/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:37:18 by thorgal           #+#    #+#             */
/*   Updated: 2025/05/13 14:49:32 by tordner          ###   ########.fr       */
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

struct s_philosopher;

typedef struct s_data
{
	int						num_philosophers;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						num_times_must_eat;
	struct s_philosopher	*philos;
	pthread_mutex_t			*forks;

	long			start_time;

	pthread_mutex_t *write;
	pthread_mutex_t *death;
	pthread_mutex_t *meal_time;
}	t_data;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	int				meals_eaten;
	long			last_meal_time;

	t_data			*data;
}	t_philosopher;



int		parse_arguments(t_data *data, int ac, char **av);

void	cleanup_simulation(t_data *data);

int		start_table(t_data *data);

int	init_table(t_data *data);

int		ft_atoi(const char *str);
void	log_state(t_philosopher *philo, int id, const char *state);
long	get_time_ms(void);
void	precise_usleep(long duration_us);

#endif