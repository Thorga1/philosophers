/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:48:07 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/17 18:38:11 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(t_data *data, int t_death)
{
	size_t	time;

	time = get_time();
	while (data->dead != 1)
	{
		if (get_time() - time >= (size_t)t_death)
			break ;
		usleep(100);
	}
}

void	message(t_philo *philo, char *msg)
{
	size_t	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write);
	if (philo->data->finished != 1 && philo->data->dead != 1)
	{
		printf("%ld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->write);
}

size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - 48) + res * 10;
		i++;
	}
	return (res * sign);
}
