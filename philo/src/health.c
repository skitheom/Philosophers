/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:56:38 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/08 13:56:27 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_starvation(t_ctrl *ctrl, u_int64_t last_meal)
{
	const u_int64_t	current_time = get_current_time();

	if (current_time == 0)
	{
		set_error_flag_on(ctrl);
		return (false);
	}
	return (current_time - last_meal > ctrl->time_to_die);
}

static bool	confirm_death(t_philo *philo)
{
	bool	is_starving;
	bool	lock_success;

	if (get_eat_flag(philo, &lock_success) || !lock_success)
		return (false);
	is_starving = false;
	if (try_lock(&philo->ctrl->locks[MEAL_LOCK]))
	{
		is_starving = check_starvation(philo->ctrl, philo->last_meal);
		pthread_mutex_unlock(&philo->ctrl->locks[MEAL_LOCK]);
		return (is_starving);
	}
	return (false);
}

bool	all_healthy(t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (i < ctrl->num_of_philos)
	{
		if (confirm_death(&ctrl->philos[i]))
		{
			display_message(ctrl, 0, ctrl->philos[i].id, MSG_DIE);
			set_dead_flag_on(ctrl);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	is_healthy(t_ctrl *ctrl)
{
	bool	lock_success;

	lock_success = false;
	if (get_error_flag(ctrl, &lock_success) && lock_success)
		return (false);
	if (get_dead_flag(ctrl, &lock_success) && lock_success)
		return (false);
	return (true);
}

bool	self_health_check(t_philo *philo)
{
	if (!is_healthy(philo->ctrl) || confirm_death(philo))
		return (false);
	return (true);
}
