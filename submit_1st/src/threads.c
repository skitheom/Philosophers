/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:58 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/08 13:45:40 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	try_lock(pthread_mutex_t *lock)
{
	int	i;

	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(lock) == 0)
			return (true);
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	return (false);
}

static bool	wait_for_philos(t_philo *philos, int num_of_philos)
{
	bool	result;
	int		i;

	result = true;
	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			result = false;
		i++;
	}
	return (result);
}

static bool	launch_philos(t_philo *philos, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, &philo_routine,
				(void *)&philos[i]) != 0)
		{
			wait_for_philos(philos, i);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	launch_threads(t_ctrl *ctrl, t_philo *philos)
{
	pthread_t	supervisor;
	pthread_t	printer;
	bool		result;

	if (pthread_create(&supervisor, NULL, &supervise, (void *)ctrl) != 0)
		return (false);
	if (pthread_create(&printer, NULL, &print_routine, (void *)ctrl) != 0)
	{
		set_error_flag_on(ctrl);
		pthread_join(supervisor, NULL);
		return (false);
	}
	if (!launch_philos(philos, ctrl->num_of_philos))
	{
		set_error_flag_on(ctrl);
		pthread_join(supervisor, NULL);
		pthread_join(printer, NULL);
		return (false);
	}
	result = true;
	result &= wait_for_philos(philos, ctrl->num_of_philos);
	result &= (pthread_join(printer, NULL) == 0);
	result &= (pthread_join(supervisor, NULL) == 0);
	return (result);
}
