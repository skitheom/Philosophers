/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:52 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/08 13:46:52 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_msg	*prepare_message(u_int64_t timestamp, int id, const char *str)
{
	t_msg	*msg;

	msg = malloc(sizeof(t_msg));
	if (!msg)
		return (NULL);
	msg->timestamp = timestamp;
	msg->id = id;
	msg->str = str;
	msg->next_msg = NULL;
	return (msg);
}

static void	ensure_timestamp_order(t_ctrl *ctrl, t_msg *msg)
{
	t_msg	*tmp;

	if (!ctrl->msg_queue || ctrl->msg_queue->timestamp > msg->timestamp)
	{
		msg->next_msg = ctrl->msg_queue;
		ctrl->msg_queue = msg;
		return ;
	}
	tmp = ctrl->msg_queue;
	while (tmp->next_msg && tmp->next_msg->timestamp <= msg->timestamp)
		tmp = tmp->next_msg;
	msg->next_msg = tmp->next_msg;
	tmp->next_msg = msg;
}

static bool	enqueue_msg(t_ctrl *ctrl, t_msg *msg)
{
	if (!try_lock(&ctrl->locks[MSG_LOCK]))
		return (false);
	ensure_timestamp_order(ctrl, msg);
	pthread_mutex_unlock(&ctrl->locks[MSG_LOCK]);
	return (true);
}

void	display_message(t_ctrl *ctrl, u_int64_t cur_ts, int id, const char *str)
{
	t_msg		*msg;
	u_int64_t	elapsed_time;

	if (cur_ts == 0)
		elapsed_time = get_elapsed_time(ctrl);
	else
		elapsed_time = cur_ts - ctrl->start_time;
	msg = prepare_message(elapsed_time, id, str);
	if (!msg)
	{
		set_error_flag_on(ctrl);
		return ;
	}
	enqueue_msg(ctrl, msg);
}
