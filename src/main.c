/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:35:30 by mcourtin          #+#    #+#             */
/*   Updated: 2023/03/13 16:19:01 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_philo(t_data *data, t_philo *philo)
{
	int	i;
	int	start_time;

	i = 0;
	start_time = get_time();
	while (i < data->philo)
	{
		philo[i].id = i;
		philo[i].nb_ate = 0;
		philo[i].starving_time = start_time;
		philo[i].philo = data->philo;
		philo[i].lifetime = data->lifetime;
		philo[i].eatime = data->eatime;
		philo[i].sleeptime = data->sleeptime;
		philo[i].cycle = data->cycle;
		philo[i].fork = data->fork;
		philo[i].start_time = start_time;
		philo[i].dead = data->dead;
		philo[i].mutex = data->mutex;
		philo[i].print = data->print;
		i++;
	}
	return (0);
}

static int	thread_philo(t_data *data, t_philo *philo)
{
	int			i;
	int			verif;

	i = 0;
	while (i < data->philo)
	{
		verif = pthread_create(&philo[i].thread, NULL, &routine, philo + i);
		if (verif != 0)
			return (create_thread_error(i));
		i++;
	}
	thread_died(philo);
	i = 0;
	while (i < data->philo)
	{
		verif = pthread_join(philo[i].thread, NULL);
		if (verif != 0)
			return (join_thread_error(i));
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;
	int		verif;

	if (ac != 5 && ac != 6)
		return (-1);
	verif = init_data(ac, av, &data);
	if (verif == 1)
		return (1);
	verif = init_mutex(&data);
	if (verif == 1)
	{
		free_mutex(&data);
		return (2);
	}
	philo = malloc(sizeof(t_philo) * data.philo);
	if (!philo)
		return (free_all(&data, philo));
	init_philo(&data, philo);
	thread_philo(&data, philo);
	free_all(&data, philo);
	return (0);
}
