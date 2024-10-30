#include "philo.h"

static void	update_meal(t_philo *philo)
{
	if (!health_check(philo))
		return ;
	if (try_lock(philo->ctrl, &philo->ctrl->meal_lock))
	{
		display_philo_msg(philo, MSG_EAT);
		philo->last_meal = get_current_time(philo->ctrl);
		philo->eaten_meals_count++;
		pthread_mutex_unlock(&philo->ctrl->meal_lock);
		return ;
	}
	set_error_flag_on(philo->ctrl);
}

static bool	try_eat(t_philo *philo, pthread_mutex_t *fork1,
		pthread_mutex_t *fork2)
{
	if (!health_check(philo) || !try_lock(philo->ctrl, fork1))
		return (false);
	display_philo_msg(philo, MSG_FORK_TAKEN);
	while (health_check(philo))
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
	while (health_check(philo))
	{
		if (philo->id % 2 == 0)
		{
			if (try_eat(philo, philo->left_fork, philo->right_fork))
				return ;
		}
		else
		{
			usleep(500);
			if (try_eat(philo, philo->right_fork, philo->left_fork))
				return ;
		}
	}
}
