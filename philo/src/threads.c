/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:58 by sakitaha          #+#    #+#             */
/*   Updated: 2024/10/31 01:14:58 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	wait_for_philos(t_philo *philos, int num_of_philos)
{
	bool	result;
	int		i;

	result = true;
	i = 0;
	while (i < num_of_philos)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			result = false;
		}
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
	return (wait_for_philos(philos, num_of_philos));
}

bool	launch_threads(t_ctrl *ctrl, t_philo *philos, int num_of_philos)
{
	pthread_t	supervisor;
	bool		result;

	if (pthread_create(&supervisor, NULL, &supervise, (void *)ctrl) != 0)
		return (false);
	result = true;
	if (!launch_philos(philos, num_of_philos))
		result = false;
	if (pthread_join(supervisor, NULL) != 0)
		result = false;
	return (result);
}
