/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:58:50 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/07 18:58:56 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_error_flag(t_ctrl *ctrl, bool *lock_success)
{
	bool	error_state;
	int		i;

	*lock_success = false;
	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&ctrl->locks[ERROR_LOCK]) == 0)
		{
			error_state = ctrl->error_flag;
			pthread_mutex_unlock(&ctrl->locks[ERROR_LOCK]);
			*lock_success = true;
			return (error_state);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	return (false);
}

bool	set_error_flag_on(t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&ctrl->locks[ERROR_LOCK]) == 0)
		{
			ctrl->error_flag = true;
			pthread_mutex_unlock(&ctrl->locks[ERROR_LOCK]);
			return (true);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	return (false);
}
