/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_dead.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:00:23 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/07 19:00:26 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_dead_flag(t_ctrl *ctrl, bool *lock_success)
{
	bool	dead_state;
	int		i;

	*lock_success = false;
	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&ctrl->locks[DEAD_LOCK]) == 0)
		{
			dead_state = ctrl->dead_flag;
			pthread_mutex_unlock(&ctrl->locks[DEAD_LOCK]);
			*lock_success = true;
			return (dead_state);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	return (false);
}

bool	set_dead_flag_on(t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&ctrl->locks[DEAD_LOCK]) == 0)
		{
			ctrl->dead_flag = true;
			pthread_mutex_unlock(&ctrl->locks[DEAD_LOCK]);
			return (true);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	return (false);
}
