/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:10:54 by sakitaha          #+#    #+#             */
/*   Updated: 2024/11/18 01:22:38 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO: 呼び出し側でのエラー処理を再確認
u_int64_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((u_int64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

u_int64_t	get_elapsed_time(t_ctrl *ctrl)
{
	const u_int64_t	current_time = get_current_time();

	if (current_time == 0)
	{
		set_error_flag_on(ctrl);
		return (0);
	}
	return (current_time - ctrl->start_time);
}

// TODO: utilじゃなくてphilo routineか、timeに移す
void	philo_sleep(t_ctrl *ctrl, u_int64_t time_to_sleep)
{
	const u_int64_t	start = get_current_time();
	u_int64_t		now;

	if (start == 0)
	{
		set_error_flag_on(ctrl);
		return ;
	}
	while (true)
	{
		now = get_current_time();
		if (now == 0)
		{
			set_error_flag_on(ctrl);
			return ;
		}
		if (now - start >= time_to_sleep)
			break ;
		usleep(PHILO_SLEEP_INTERVAL);
	}
}
