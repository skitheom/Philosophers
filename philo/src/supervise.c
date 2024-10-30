#include "philo.h"

static bool	confirm_death(t_philo *philo, size_t time_to_die)
{
	size_t	current_time;
	bool	is_starving;

	if (philo->eating)
		return (false);
	is_starving = false;
	if (try_lock(philo->ctrl, &philo->ctrl->meal_lock))
	{
		current_time = get_current_time(philo->ctrl);
		if (current_time - philo->last_meal >= time_to_die
			&& current_time != SIZE_MAX)
			is_starving = true;
		pthread_mutex_unlock(&philo->ctrl->meal_lock);
		return (is_starving);
	}
	set_error_flag_on(philo->ctrl);
	return (false);
}

static bool	all_healthy(t_ctrl *ctrl)
{
	t_philo			*philos;
	const size_t	time_to_die = ctrl->config.time_to_die;
	const int		num_of_philos = ctrl->config.num_of_philos;
	int				i;

	if (!is_healthy(ctrl))
		return (false);
	philos = ctrl->philos;
	i = 0;
	while (i < num_of_philos)
	{
		if (confirm_death(&philos[i], time_to_die))
		{
			display_philo_msg(&philos[i], MSG_DIE);
			set_dead_flag_on(ctrl);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	confirm_hungry(t_philo *philo, int num_of_times_to_eat)
{
	bool	is_hungry;

	is_hungry = false;
	if (try_lock(philo->ctrl, &philo->ctrl->meal_lock))
	{
		is_hungry = philo->eaten_meals_count < num_of_times_to_eat;
		pthread_mutex_unlock(&philo->ctrl->meal_lock);
		return (is_hungry);
	}
	set_error_flag_on(philo->ctrl);
	return (false);
}

static bool	still_hungry(t_ctrl *ctrl)
{
	t_philo		*philos;
	const int	num_of_times_to_eat = ctrl->config.num_of_times_to_eat;
	const int	num_of_philos = ctrl->config.num_of_philos;
	int			i;

	if (!is_healthy(ctrl))
		return (false);
	philos = ctrl->philos;
	i = 0;
	while (i < num_of_philos)
	{
		if (confirm_hungry(&philos[i], num_of_times_to_eat))
			return (true);
		i++;
	}
	return (false);
}

void	*supervise(void *ptr)
{
	t_ctrl	*ctrl;

	ctrl = (t_ctrl *)ptr;
	while (true)
	{
		if (!all_healthy(ctrl) || !still_hungry(ctrl))
			break ;
	}
	return (ptr);
}
