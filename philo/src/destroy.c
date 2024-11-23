/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:08:05 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/23 18:08:16 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(pthread_mutex_t mutexes[], int size)
{
	int	i;

	if (!mutexes || size < 1)
		return ;
	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
}

void	destroy_philo_mutexes(t_philo *philos, int size)
{
	int	i;

	if (!philos || size < 1)
		return ;
	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&philos[i].meal_lock);
		i++;
	}
}
