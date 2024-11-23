/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_eat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:01:10 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/23 17:35:43 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_eat_flag(t_philo *philo, bool *lock_success)
{
	bool	eating_state;
	int		i;

	*lock_success = false;
	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&philo->meal_lock) == 0)
		{
			eating_state = philo->eating;
			pthread_mutex_unlock(&philo->meal_lock);
			*lock_success = true;
			return (eating_state);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	return (false);
}

bool	set_eat_flag(t_philo *philo, bool state)
{
	int	i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&philo->meal_lock) == 0)
		{
			philo->eating = state;
			pthread_mutex_unlock(&philo->meal_lock);
			return (true);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	return (false);
}

bool	set_eat_flag_on(t_philo *philo, u_int64_t beginning_of_last_meal)
{
	int	i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&philo->meal_lock) == 0)
		{
			philo->eating = true;
			philo->last_meal = beginning_of_last_meal;
			pthread_mutex_unlock(&philo->meal_lock);
			return (true);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	return (false);
}

bool	set_eat_flag_off(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&philo->meal_lock) == 0)
		{
			philo->eating = false;
			philo->eaten_meals_count++;
			pthread_mutex_unlock(&philo->meal_lock);
			return (true);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	return (false);
}
