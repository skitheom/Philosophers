/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:44 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/08 13:06:11 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	nap(t_philo *philo)
{
	if (!self_health_check(philo))
		return ;
	display_message(philo->ctrl, 0, philo->id, MSG_SLEEP);
	philo_sleep(philo->ctrl, philo->ctrl->time_to_sleep);
}

static void	think(t_philo *philo)
{
	if (!self_health_check(philo))
		return ;
	display_message(philo->ctrl, 0, philo->id, MSG_THINK);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		philo_sleep(philo->ctrl, DELAY);
	while (self_health_check(philo))
	{
		eat(philo);
		nap(philo);
		think(philo);
	}
	return (ptr);
}
