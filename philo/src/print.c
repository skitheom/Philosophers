/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:14:48 by sakitaha          #+#    #+#             */
/*   Updated: 2024/10/31 03:29:04 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_error(const char *str)
{
	return (write(2, str, ft_strlen(str)) != -1);
}

bool	safe_print(t_ctrl *ctrl, int fd, const char *str)
{
	int	result;
	int	i;

	result = -1;
	i = 0;
	while (i < MAX_RETRY)
	{
		if (pthread_mutex_lock(&ctrl->write_lock) == 0)
		{
			result = write(fd, str, ft_strlen(str));
			pthread_mutex_unlock(&ctrl->write_lock);
			return (result != -1);
		}
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	print_error(ERR_WRITE);
	return (false);
}

static char	*format_msg(char *time_str, char *id, const char *str)
{
	char		*dest;
	const char	*single_space = " ";
	size_t		len;

	len = ft_strlen(time_str) + ft_strlen(id) + ft_strlen(str) + 4;
	dest = malloc(len);
	if (!dest)
		return (NULL);
	memset(dest, 0, len);
	ft_strlcpy(dest, time_str, len);
	ft_strlcat(dest, single_space, len);
	ft_strlcat(dest, id, len);
	ft_strlcat(dest, single_space, len);
	ft_strlcat(dest, str, len);
	return (dest);
}

static void	print_msg(t_ctrl *ctrl, char *time_str, char *id_str,
		const char *str)
{
	char	*msg;

	msg = format_msg(time_str, id_str, str);
	if (!msg)
	{
		safe_print(ctrl, 2, ERR_PHILO_MSG);
		return ;
	}
	safe_print(ctrl, 1, msg);
	xfree(msg);
}

void	*output_routine(void *ptr)
{
	t_msg	*msg;
	size_t	timestamp;
	char	*time_str;
	char	*id_str;

	msg = (t_msg *)ptr;
	timestamp = get_current_time(msg->philo->ctrl);
	if (timestamp == SIZE_MAX)
	{
		xfree(msg);
		return (NULL);
	}
	time_str = ft_utoa(timestamp);
	id_str = ft_itoa(msg->philo->id);
	if (!time_str || !id_str)
	{
		xfree(time_str);
		xfree(id_str);
		xfree(msg);
		safe_print(msg->philo->ctrl, 2, ERR_PHILO_MSG);
		return (NULL);
	}
	print_msg(msg->philo->ctrl, time_str, id_str, msg->str);
	xfree(time_str);
	xfree(id_str);
	xfree(msg);
	return (NULL);
}

void	display_philo_msg(t_philo *philo, const char *str)
{
	pthread_t	output_thread;
	t_msg		*msg;

	msg = malloc(sizeof(t_msg));
	if (!msg)
	{
		set_error_flag_on(philo->ctrl);
		return ;
	}
	msg->philo = philo;
	msg->str = str;
	pthread_create(&output_thread, NULL, output_routine, (void *)msg);
	pthread_detach(output_thread);
}
