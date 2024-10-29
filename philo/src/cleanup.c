#include "philo.h"

void	destroy_mutex_forks(t_ctrl *ctrl)
{
	int	i;

	if (!ctrl->forks)
		return ;
	i = 0;
	while (i < ctrl->config.num_of_philos)
	{
		pthread_mutex_destroy(&ctrl->forks[i]);
		i++;
	}
}

void	destroy_mutex_locks(t_ctrl *ctrl)
{
	pthread_mutex_destroy(&ctrl->dead_lock);
	pthread_mutex_destroy(&ctrl->meal_lock);
	pthread_mutex_destroy(&ctrl->write_lock);
}

void	cleanup_memory(t_ctrl *ctrl)
{
	if (ctrl->philos)
		free(ctrl->philos);
	if (ctrl->forks)
		free(ctrl->forks);
}

void	cleanup_ctrl(t_ctrl *ctrl)
{
	destroy_mutex_forks(ctrl);
	destroy_mutex_locks(ctrl);
	cleanup_memory(ctrl);
}
