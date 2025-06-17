/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:43:08 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/17 18:37:18 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					meal_count;
	int					id;
	size_t				last_meal;
	struct s_data		*data;
	struct s_philo		*left_fork;
	struct s_philo		*right_fork;
	pthread_mutex_t		fork;
}					t_philo;

typedef struct s_data
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_philosophers;
	int					num_times_must_eat;
	size_t				start_time;
	int					finished;
	int					dead;
	t_philo				*philos;
	pthread_mutex_t		write;
	pthread_mutex_t		lock;
}					t_data;

void	death(t_data *data);

int		check_error(int ac, char **av);

t_data	*setup_data(int ac, char **av);

int		start_table(t_data *data, pthread_t *philo_threads);
void	*routine(void *arg);

void	my_sleep(t_data *data, int t_death);
void	message(t_philo *philo, char *msg);
size_t	get_time(void);
int		ft_atoi(char *str);

#endif