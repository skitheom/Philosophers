/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:35 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/18 01:21:52 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	setup_values(t_ctrl *ctrl, const char **argv)
{
	ctrl->num_of_philos = convert_input_to_num(argv[1]);
	ctrl->time_to_die = (u_int64_t)convert_input_to_num(argv[2]);
	ctrl->time_to_eat = convert_input_to_num(argv[3]);
	ctrl->time_to_sleep = convert_input_to_num(argv[4]);
	if (argv[5])
		ctrl->num_of_times_to_eat = convert_input_to_num(argv[5]);
	else
		ctrl->num_of_times_to_eat = -1;
	ctrl->start_time = 0;
	ctrl->dead_flag = false;
	ctrl->error_flag = false;
	ctrl->msg_queue = NULL;
}

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

static bool	setup_mutexes(t_ctrl *ctrl)
{
	if (!init_mutexes(ctrl->forks, ctrl->num_of_philos))
		return (false);
	if (!init_mutexes(ctrl->locks, NUM_LOCKS))
	{
		destroy_mutexes(ctrl->forks, ctrl->num_of_philos);
		return (false);
	}
	return (true);
}

static bool	setup_philos(t_ctrl *ctrl)
{
	const u_int64_t	current_time = get_current_time();
	const int		max_philos = ctrl->num_of_philos;
	int				i;

	if (current_time == 0)
		return (false);
	i = 0;
	while (i < max_philos)
	{
		ctrl->philos[i].id = i + 1;
		ctrl->philos[i].eaten_meals_count = 0;
		ctrl->philos[i].eating = false;
		ctrl->philos[i].last_meal = current_time;
		ctrl->philos[i].left_fork = &(ctrl->forks[i]);
		if (i == 0)
			ctrl->philos[i].right_fork = &(ctrl->forks[max_philos - 1]);
		else
			ctrl->philos[i].right_fork = &(ctrl->forks[i - 1]);
		ctrl->philos[i].ctrl = ctrl;
		i++;
	}
	return (true);
}

bool	init_ctrl(t_ctrl *ctrl, const char **argv)
{
	setup_values(ctrl, argv);
	ctrl->philos = malloc(sizeof(t_philo) * ctrl->num_of_philos);
	ctrl->forks = malloc(sizeof(pthread_mutex_t) * ctrl->num_of_philos);
	if (!ctrl->philos || !ctrl->forks || !setup_mutexes(ctrl))
	{
		cleanup_memory(ctrl);
		return (false);
	}
	if (!setup_philos(ctrl))
	{
		cleanup_ctrl(ctrl);
		return (false);
	}
	ctrl->start_time = get_current_time();
	return (ctrl->start_time != 0);
}
