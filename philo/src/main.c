/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:38 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/23 18:39:17 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO : 提出前にcomment outする
// #include <libc.h>
// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }

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

int	main(int argc, const char **argv)
{
	t_ctrl	ctrl;

	if (!validate_argv(argc, argv))
		return (EXIT_FAILURE);
	setup_values(&ctrl, argv);
	if (!init_ctrl(&ctrl))
	{
		print_error(ERR_INIT);
		return (EXIT_FAILURE);
	}
	if (!launch_threads(&ctrl, ctrl.philos))
	{
		print_error(ERR_LAUNCH_THREAD);
		cleanup_msg(&ctrl);
		cleanup_ctrl(&ctrl);
		return (EXIT_FAILURE);
	}
	cleanup_msg(&ctrl);
	cleanup_ctrl(&ctrl);
	return (EXIT_SUCCESS);
}
