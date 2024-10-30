#include "philo.h"

bool	try_lock(t_ctrl *ctrl, pthread_mutex_t *lock)
{
	int	i;

	i = 0;
	while (i < MAX_RETRY && is_healthy(ctrl))
	{
		if (pthread_mutex_lock(lock) == 0)
			return (true);
		usleep(USLEEP_RETRY_INTERVAL);
		i++;
	}
	return (false);
}

static void	nap(t_philo *philo)
{
	display_philo_msg(philo, MSG_SLEEP);
	philo_sleep(philo->ctrl, philo->ctrl->config.time_to_sleep);
}

static void	think(t_philo *philo)
{
	display_philo_msg(philo, MSG_THINK);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0) // あとでみなおし
		philo_sleep(philo->ctrl, 10);
	while (is_healthy(philo->ctrl))
	{
		eat(philo);
		nap(philo);
		think(philo);
	}
	return (ptr);
}
