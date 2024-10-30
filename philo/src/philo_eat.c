#include "philo.h"

static void	update_meal(t_philo *philo)
{
	if (!is_healthy(philo->ctrl))
		return ;
	if (try_lock(philo->ctrl, &philo->ctrl->meal_lock))
	{
		display_philo_msg(philo, MSG_EAT);
		philo->last_meal = get_current_time();
		philo->eaten_meals_count++;
		pthread_mutex_unlock(&philo->ctrl->meal_lock);
	}
	set_error_flag_on(philo->ctrl);
}

static bool	try_eat(t_philo *philo, pthread_mutex_t *fork1,
		pthread_mutex_t *fork2)
{
	if (!try_lock(philo->ctrl, fork1))
		return (false);
	display_philo_msg(philo, MSG_FORK_TAKEN);
	while (is_healthy(philo->ctrl))
	{
		if (try_lock(philo->ctrl, fork2))
		{
			display_philo_msg(philo, MSG_FORK_TAKEN);
			philo->eating = true;
			update_meal(philo);
			philo_sleep(philo->ctrl, philo->ctrl->config.time_to_eat);
			philo->eating = false;
			pthread_mutex_unlock(fork2);
			break ;
		}
		usleep(USLEEP_RETRY_INTERVAL);
	}
	pthread_mutex_unlock(fork1);
	return (true);
}

void	eat(t_philo *philo)
{
	int	i;

	i = philo->id % 2;
	while (is_healthy(philo->ctrl))
	{
		if (i % 2 == 0 && try_eat(philo, philo->left_fork, philo->right_fork))
			return ;
		else if (try_eat(philo, philo->right_fork, philo->left_fork))
			return ;
		i++;
	}
}
