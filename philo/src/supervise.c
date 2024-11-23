/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:52 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/23 18:32:37 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	confirm_hungry(t_philo *philo, int num_of_times_to_eat)
{
	bool	is_hungry;

	is_hungry = false;
	if (try_lock(&philo->meal_lock))
	{
		is_hungry = philo->eaten_meals_count < num_of_times_to_eat;
		pthread_mutex_unlock(&philo->meal_lock);
		return (is_hungry);
	}
	return (false);
}

static bool	still_hungry(t_ctrl *ctrl)
{
	int	i;

	if (ctrl->num_of_times_to_eat == -1)
		return (true);
	i = 0;
	while (i < ctrl->num_of_philos)
	{
		if (confirm_hungry(&ctrl->philos[i], ctrl->num_of_times_to_eat))
			return (true);
		i++;
	}
	set_dead_flag_on(ctrl);
	return (false);
}

void	*supervise(void *ptr)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *)ptr;
	while (true)
	{
		if (!is_healthy(ctrl) || !all_healthy(ctrl) || !still_hungry(ctrl))
			break ;
		usleep(SUPERVISE_SLEEP_INTERVAL);
	}
	return (ptr);
}
