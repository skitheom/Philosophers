/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:16 by sakitaha          #+#    #+#             */
/*   Updated: 2024/10/31 02:28:41 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_eat_flag(t_philo *philo, bool *lock_success)
{
	bool	eating_state;
	int		i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&philo->ctrl->meal_lock) == 0)
		{
			eating_state = philo->eating;
			pthread_mutex_unlock(&philo->ctrl->meal_lock);
			*lock_success = true;
			return (eating_state);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	safe_print(philo->ctrl, 2, ERR_ERROR_FLAG);
	*lock_success = false;
	return (false);
}

bool	set_error_flag_on(t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&ctrl->error_lock) == 0)
		{
			ctrl->error_flag = true;
			pthread_mutex_unlock(&ctrl->error_lock);
			return (true);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	safe_print(ctrl, 2, ERR_ERROR_FLAG);
	return (false);
}

static bool	get_error_flag(t_ctrl *ctrl, bool *lock_success)
{
	bool	error_state;
	int		i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&ctrl->error_lock) == 0)
		{
			error_state = ctrl->error_flag;
			pthread_mutex_unlock(&ctrl->error_lock);
			*lock_success = true;
			return (error_state);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	safe_print(ctrl, 2, ERR_ERROR_FLAG);
	*lock_success = false;
	return (false);
}

bool	set_dead_flag_on(t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&ctrl->dead_lock) == 0)
		{
			ctrl->dead_flag = true;
			pthread_mutex_unlock(&ctrl->dead_lock);
			return (true);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	safe_print(ctrl, 2, ERR_DEAD_FLAG);
	return (false);
}

static bool	get_dead_flag(t_ctrl *ctrl, bool *lock_success)
{
	bool	dead_state;
	int		i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&ctrl->dead_lock) == 0)
		{
			dead_state = ctrl->dead_flag;
			pthread_mutex_unlock(&ctrl->dead_lock);
			*lock_success = true;
			return (dead_state);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	safe_print(ctrl, 2, ERR_DEAD_FLAG);
	*lock_success = false;
	return (false);
}

bool	is_healthy(t_ctrl *ctrl)
{
	bool	check_err_success;
	bool	check_dead_success;

	check_err_success = false;
	check_dead_success = false;
	if (get_error_flag(ctrl, &check_err_success) || get_dead_flag(ctrl,
			&check_dead_success))
		return (false);
	if (!check_err_success || !check_dead_success)
	{
		safe_print(ctrl, 2, "<< Set Error Flag at is_healthy() >>\n");
		set_error_flag_on(ctrl);
		return (false);
	}
	return (true);
}
