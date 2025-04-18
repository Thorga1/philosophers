/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorgal <thorgal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:53:49 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/14 16:08:50 by thorgal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Malloc error");
	return (ret);
}

static void	handle_mutex_errors(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode
			|| DESTROY == opcode))
		error_exit("Value specified by mutex is invalid.");
	else if (EINVAL == status && INIT == opcode)
		error_exit("Value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread"
			" blocked waiting for a mutex.");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on a mutex.");
	else if (EBUSY == status)
		error_exit("Mutex is locked.");
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_errors(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_errors(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_errors(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_errors(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode sent to mutex handler.");
}

static void	handle_thread_errors(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("No ressources to create another thread.");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate permission.");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by thread isn't joinable.");
	else if (ESRCH == status)
		error_exit("No thread found correspoonding to given thread ID.");
	else if (EDEADLK == status)
		error_exit("Deadlock detected or value "
			"of thread specifies calling thread");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_errors(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_errors(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_errors(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode sent to thread handler.");
}
