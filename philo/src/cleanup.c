/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:11 by sakitaha          #+#    #+#             */
/*   Updated: 2024/10/31 01:14:12 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex_locks(t_ctrl *ctrl)
{
	pthread_mutex_destroy(&ctrl->dead_lock);
	pthread_mutex_destroy(&ctrl->meal_lock);
	pthread_mutex_destroy(&ctrl->write_lock);
	pthread_mutex_destroy(&ctrl->error_lock);
}

void	destroy_mutex_forks(t_ctrl *ctrl)
{
	int	i;

	if (!ctrl->forks)
		return ;
	i = 0;
	while (i < ctrl->config.num_of_philos)
	{
		pthread_mutex_destroy(&ctrl->forks[i]);
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
	destroy_mutex_locks(ctrl);
	destroy_mutex_forks(ctrl);
	cleanup_memory(ctrl);
}
