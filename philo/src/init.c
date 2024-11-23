/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:35 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/23 18:30:09 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_mutexes(pthread_mutex_t mutexes[], int size)
{
	int	i;

	if (!mutexes || size < 1)
		return (false);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			destroy_mutexes(mutexes, i);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	setup_philo_mutexes(t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (i < ctrl->num_of_philos)
	{
		if (pthread_mutex_init(&ctrl->philos[i].meal_lock, NULL) != 0)
		{
			destroy_philo_mutexes(ctrl->philos, i);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	setup_mutexes(t_ctrl *ctrl)
{
	if (!init_mutexes(ctrl->forks, ctrl->num_of_philos))
		return (false);
	if (!init_mutexes(ctrl->locks, NUM_LOCKS))
	{
		destroy_mutexes(ctrl->forks, ctrl->num_of_philos);
		return (false);
	}
	if (!setup_philo_mutexes(ctrl))
	{
		destroy_mutexes(ctrl->forks, ctrl->num_of_philos);
		destroy_mutexes(ctrl->locks, NUM_LOCKS);
		return (false);
	}
	return (true);
}

static bool	setup_philos(t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (i < ctrl->num_of_philos)
	{
		ctrl->philos[i].id = i + 1;
		ctrl->philos[i].eating = false;
		ctrl->philos[i].last_meal = ctrl->start_time;
		ctrl->philos[i].eaten_meals_count = 0;
		ctrl->philos[i].left_fork = &(ctrl->forks[i]);
		ctrl->philos[i].right_fork = &(ctrl->forks[(i - 1 + ctrl->num_of_philos)
				% ctrl->num_of_philos]);
		ctrl->philos[i].ctrl = ctrl;
		i++;
	}
	return (true);
}

bool	init_ctrl(t_ctrl *ctrl)
{
	ctrl->philos = malloc(sizeof(t_philo) * ctrl->num_of_philos);
	ctrl->forks = malloc(sizeof(pthread_mutex_t) * ctrl->num_of_philos);
	if (!ctrl->philos || !ctrl->forks || !setup_mutexes(ctrl))
	{
		cleanup_memory(ctrl);
		return (false);
	}
	ctrl->start_time = get_current_time();
	if (ctrl->start_time == 0 || !setup_philos(ctrl))
	{
		cleanup_ctrl(ctrl);
		return (false);
	}
	return (true);
}
