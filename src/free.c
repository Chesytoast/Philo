/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:52:36 by mcourtin          #+#    #+#             */
/*   Updated: 2023/03/13 16:14:50 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	free_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (data->fork)
	{
		while (i < data->philo)
		{
			if (data->fork + i)
				pthread_mutex_destroy(data->fork + i);
			i++;
		}
	}
	return (1);
}

int	free_all(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	free_mutex(data);
	if (data->dead)
		free(data->dead);
	if (philo)
		free(philo);
	return (1);
}
