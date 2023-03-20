/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:14:21 by mcourtin          #+#    #+#             */
/*   Updated: 2023/03/13 16:19:21 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_check_atoi(char *str)
{
	size_t		i;
	int			s;
	int			f;
	int			ftmp;

	f = 0;
	s = 1;
	i = 0;
	ftmp = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			return (negative_error(str));
	while (str[i] <= '9' && str [i] >= '0')
	{
		ftmp = f;
		f = f * 10 + (str[i++] - 48);
		if (ftmp > f)
			return (max_value_error(str));
	}
	if (str[i] != '\0' || str[0] == '\0')
		return (bad_input(str, "is a bad input"));
	return ((int)f);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_sleep(int time)
{
	int	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return ;
}

void	print_action(t_philo *philo, char *s)
{
	int	time;

	pthread_mutex_lock(philo->mutex);
	if (philo->dead[0] == 0)
	{
		pthread_mutex_lock(philo->print);
		time = get_time() - philo->start_time;
		printf("%d\t%d %s\n", time, philo->id, s);
		pthread_mutex_unlock(philo->print);
	}
	pthread_mutex_unlock(philo->mutex);
}
