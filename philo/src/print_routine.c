

/* void	display_philo_msg(t_philo *philo, const char *str)
{
	size_t	timestamp;
	char	*time_str;
	char	*id_str;

	timestamp = get_current_time(philo->ctrl);
	if (timestamp == SIZE_MAX)
		return ;
	time_str = ft_utoa(timestamp);
	id_str = ft_itoa(philo->id);
	if (!time_str || !id_str)
	{
		xfree(time_str);
		xfree(id_str);
		safe_print(philo->ctrl, 2, ERR_PHILO_MSG);
		return ;
	}
	if (is_healthy(philo->ctrl))
		print_msg(philo->ctrl, time_str, id_str, str);
	xfree(time_str);
	xfree(id_str);
}
 */
