/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:37:18 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/14 17:03:34 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define RST	"\033[0m"
# define R		"\033[0;31m"
# define G		"\033[0;32m"
# define Y		"\033[0;33m"
# define B		"\033[0;34m"
# define M		"\033[0;35m"
# define C		"\033[0;36m"
# define W		"\033[0;37m"

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef pthread_mutex_t	t_mtx;

typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	long	start_simulation;
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals; // if -1 no limit
	bool	end_simulation;
	bool	all_threads_ready;
	t_mtx	write_mutex;
	t_mtx	table_mutex;
	t_fork	*forks;
	t_philo	*philos;
}	t_table;

void	error_exit(const char *error);
long	gettime(t_time_code time_code);

void	parse_input(t_table	*table, char **av);

void	*safe_malloc(size_t bytes);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);

void	data_init(t_table *table);

bool	simulation_finished(t_table *table);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx	*mutex, long *value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);

void	wait_all_threads(t_table *table);

#endif