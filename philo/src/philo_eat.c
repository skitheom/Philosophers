/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:41 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/08 13:46:14 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	try_take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (!try_lock(fork) || !self_health_check(philo))
		return (false);
	display_message(philo->ctrl, 0, philo->id, MSG_FORK_TAKEN);
	return (true);
}

void	process_eating(t_philo *philo)
{
	u_int64_t	current_time;

	current_time = get_current_time();
	if (current_time == 0)
	{
		set_error_flag_on(philo->ctrl);
		return ;
	}
	set_eat_flag_on(philo, current_time);
	if (!self_health_check(philo))
	{
		set_eat_flag(philo, false);
		return ;
	}
	display_message(philo->ctrl, current_time, philo->id, MSG_EAT);
	philo_sleep(philo->ctrl, philo->ctrl->time_to_eat);
	set_eat_flag_off(philo);
}

static bool	try_eat(t_philo *philo)
{
	int	i;

	if (!try_take_fork(philo, philo->right_fork))
		return (false);
	if (philo->ctrl->num_of_philos == 1)
	{
		philo_sleep(philo->ctrl, philo->ctrl->time_to_die);
		return (true);
	}
	i = 0;
	while (i < MAX_RETRY)
	{
		if (try_take_fork(philo, philo->left_fork))
		{
			process_eating(philo);
			pthread_mutex_unlock(philo->left_fork);
			break ;
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	pthread_mutex_unlock(philo->right_fork);
	return (i < MAX_RETRY);
}

void	eat(t_philo *philo)
{
	while (self_health_check(philo))
	{
		if (try_eat(philo))
			return ;
		usleep(USLEEP_RETRY_INTERVAL);
	}
}
