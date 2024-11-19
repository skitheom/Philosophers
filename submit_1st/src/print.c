/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:10:39 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/18 02:44:17 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_error(const char *str)
{
	return (write(2, str, ft_strlen(str)) != -1);
}

void	print_message(t_msg *msg)
{
	if (!msg)
		return ;
	printf("%lu %d %s", msg->timestamp, msg->id, msg->str);
}

static t_msg	*dequeue_msg(t_ctrl *ctrl)
{
	t_msg	*tmp;

	if (!try_lock(&ctrl->locks[MSG_LOCK]))
		return (NULL);
	if (!ctrl->msg_queue)
	{
		pthread_mutex_unlock(&ctrl->locks[MSG_LOCK]);
		return (NULL);
	}
	tmp = ctrl->msg_queue;
	ctrl->msg_queue = tmp->next_msg;
	pthread_mutex_unlock(&ctrl->locks[MSG_LOCK]);
	return (tmp);
}

void	*print_routine(void *ptr)
{
	t_ctrl	*ctrl;
	t_msg	*msg;

	ctrl = (t_ctrl *)ptr;
	while (true)
	{
		if (!is_healthy(ctrl))
			break ;
		msg = dequeue_msg(ctrl);
		if (msg)
		{
			print_message(msg);
			xfree(msg);
			continue ;
		}
		usleep(PRINT_SLEEP_INTERVAL);
	}
	return (ptr);
}
