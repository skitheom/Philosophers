#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (size != 0)
	{
		i = 0;
		while (*src && i + 1 < size)
		{
			*(dest++) = *(src++);
			i++;
		}
		*dest = '\0';
	}
	return (srclen);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;

	destlen = 0;
	if (dest)
		destlen = ft_strlen(dest);
	if (size <= destlen)
		return (size + ft_strlen(src));
	while (*dest)
		dest++;
	srclen = ft_strlcpy(dest, src, size - destlen);
	return (destlen + srclen);
}

size_t	get_current_time(t_ctrl *ctrl)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		safe_print(ctrl, 2, ERR_GET_TIME);
		set_error_flag_on(ctrl);
		return (SIZE_MAX);
	}
	return ((size_t)tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	philo_sleep(t_ctrl *ctrl, size_t time_to_sleep)
{
	const size_t	start = get_current_time(ctrl);
	size_t			now;

	if (start == SIZE_MAX)
		return ;
	while (true)
	{
		now = get_current_time(ctrl);
		if (now == SIZE_MAX || now - start >= time_to_sleep)
			return ;
		usleep(PHILO_SLEEP_INTERVAL);
	}
}
