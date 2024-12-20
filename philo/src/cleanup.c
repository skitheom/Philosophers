/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:11 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/23 18:10:18 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	destroy_philo_mutexes(ctrl->philos, ctrl->num_of_philos);
	cleanup_memory(ctrl);
}

void	cleanup_msg(t_ctrl *ctrl)
{
	t_msg	*tmp;
	t_msg	*next;
	bool	is_died;

	tmp = ctrl->msg_queue;
	ctrl->msg_queue = NULL;
	is_died = false;
	while (tmp)
	{
		next = tmp->next_msg;
		if (!is_died)
		{
			print_message(tmp);
			is_died = ft_strncmp(tmp->str, MSG_DIE, sizeof(MSG_DIE) - 1) == 0;
		}
		xfree(tmp);
		tmp = next;
	}
}
