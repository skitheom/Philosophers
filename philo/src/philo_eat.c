/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:41 by sakitaha          #+#    #+#             */
/*   Updated: 2024/10/31 02:31:00 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	set_eat_flag(t_philo *philo, bool state)
{
	int	i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&philo->ctrl->meal_lock) == 0)
		{
			philo->eating = state;
			pthread_mutex_unlock(&philo->ctrl->meal_lock);
			return (true);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	safe_print(philo->ctrl, 2, ERR_ERROR_FLAG);
	return (false);
}

static void	update_meal(t_philo *philo)
{
	if (!health_check(philo))
		return ;
	if (try_lock(philo->ctrl, &philo->ctrl->meal_lock))
	{
		display_philo_msg(philo, MSG_EAT);
		philo->last_meal = get_current_time(philo->ctrl);
		philo->eaten_meals_count++;
		pthread_mutex_unlock(&philo->ctrl->meal_lock);
		return ;
	}
	set_error_flag_on(philo->ctrl);
}

static bool	try_eat(t_philo *philo, pthread_mutex_t *fork1,
		pthread_mutex_t *fork2)
{
	if (!health_check(philo) || !try_lock(philo->ctrl, fork1))
		return (false);
	display_philo_msg(philo, MSG_FORK_TAKEN);
	while (health_check(philo))
	{
		if (fork1 != fork2 && try_lock(philo->ctrl, fork2))
		{
			set_eat_flag(philo, true);
			display_philo_msg(philo, MSG_FORK_TAKEN);
			update_meal(philo);
			philo_sleep(philo->ctrl, philo->ctrl->config.time_to_eat);
			set_eat_flag(philo, false);
			pthread_mutex_unlock(fork2);
			break ;
		}
		usleep(USLEEP_RETRY_INTERVAL);
	}
	pthread_mutex_unlock(fork1);
	return (fork1 != fork2);
}

void	eat(t_philo *philo)
{
	while (health_check(philo))
	{
		if (try_eat(philo, philo->right_fork, philo->left_fork))
			return ;
		// if (philo->id % 2 == 0)
		// {
		// 	if (try_eat(philo, philo->left_fork, philo->right_fork))
		// 		return ;
		// }
		// else
		// {
		// 	if (try_eat(philo, philo->right_fork, philo->left_fork))
		// 		return ;
		// }
	}
}
