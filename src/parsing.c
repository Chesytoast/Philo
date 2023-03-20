/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:42:23 by mcourtin          #+#    #+#             */
/*   Updated: 2023/03/13 16:23:21 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo);
	if (!data->fork)
		return (1);
	data->mutex = malloc(sizeof(pthread_mutex_t));
	if (!data->mutex)
		return (free_mutex(data));
	data->print = malloc(sizeof(pthread_mutex_t));
	if (!data->print)
		return (free_mutex(data));
	pthread_mutex_init(data->mutex, NULL);
	pthread_mutex_init(data->print, NULL);
	while (i < data->philo)
	{
		if (pthread_mutex_init(data->fork + i, NULL) != 0)
			free_mutex(data);
		i++;
	}
	return (0);
}

int	init_data(int ac, char **av, t_data *data)
{
	(void)ac;
	if (ac == 6)
	{
		data->cycle = ft_check_atoi(av[5]);
		if (data->cycle == -1)
			return (1);
	}
	data->philo = ft_check_atoi(av[1]);
	data->lifetime = ft_check_atoi(av[2]);
	data->eatime = ft_check_atoi(av[3]);
	data->sleeptime = ft_check_atoi(av[4]);
	if (data->philo < 0 || data->lifetime < 0 || data->eatime < \
	0 || data->sleeptime < 0)
		return (1);
	data->dead = malloc(sizeof(atomic_int));
	if (!data->dead)
		return (1);
	*data->dead = 0;
	if (ac == 5)
		data->cycle = -1;
	return (0);
}
