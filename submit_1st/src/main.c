/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:38 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/07 16:45:59 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_ctrl	ctrl;

	if (!validate_argv(argc, argv))
		return (EXIT_FAILURE);
	if (!init_ctrl(&ctrl, argv))
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
