#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	print_error(char *str)
{
	write(2, str, ft_strlen(str));
}

void	cleanup_ctrl(t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (i < ctrl->config->num_of_philos)
	{
		pthread_mutex_destroy(&ctrl->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&ctrl->dead_lock);
	pthread_mutex_destroy(&ctrl->meal_lock);
	pthread_mutex_destroy(&ctrl->write_lock);
	if (ctrl->config)
		free(ctrl->config);
	if (ctrl->philos)
		free(ctrl->philos);
	if (ctrl->forks)
		free(ctrl->forks);
}

int	convert_input_to_num(const char *str)
{
	char	*endptr;
	long	value;

	if (!str || !*str)
		return (-1);
	endptr = NULL;
	errno = 0;
	value = strtol(str, &endptr, 10);
	if (errno != 0 || *endptr != '\0' || value > INT_MAX || value < 0)
		return (-1);
	return ((int)value);
}

int64_t	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		print_error("Error: gettimeofday failed\n");
		return (-1);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
