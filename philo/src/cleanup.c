/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:11 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/07 16:31:22 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(pthread_mutex_t mutexes[], int size)
{
	int	i;

	if (!mutexes || size < 1)
		return ;
	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
}

void	xfree(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	cleanup_memory(t_ctrl *ctrl)
{
	xfree(ctrl->philos);
	xfree(ctrl->forks);
}

void	cleanup_ctrl(t_ctrl *ctrl)
{
	destroy_mutexes(ctrl->forks, ctrl->num_of_philos);
	destroy_mutexes(ctrl->locks, NUM_LOCKS);
	cleanup_memory(ctrl);
}

void	cleanup_msg(t_ctrl *ctrl)
{
	t_msg	*tmp;
	t_msg	*next;

	if (!ctrl->msg_queue)
		return ;
	tmp = ctrl->msg_queue;
	while (tmp)
	{
		next = tmp->next_msg;
		xfree(tmp);
		tmp = next;
	}
	ctrl->msg_queue = NULL;
}
