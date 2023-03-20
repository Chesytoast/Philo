/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:46:57 by mcourtin          #+#    #+#             */
/*   Updated: 2023/03/14 11:51:29 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_death(t_philo *philo)
{
	if (get_time() - philo->starving_time >= philo->lifetime && \
	philo->nb_ate != philo->cycle)
	{
		philo->dead[0] = 1;
		pthread_mutex_lock(philo->print);
		printf("%d\t%d died.\n", get_time() - philo->start_time, \
		philo->id);
		pthread_mutex_unlock(philo->print);
		if (philo->philo == 1)
			pthread_mutex_unlock(&philo->fork[philo->id]);
		return (0);
	}
	return (1);
}

void	thread_died(t_philo *philo)
{
	int	i;
	int	alive;
	int	full_eat;

	alive = 1;
	while (alive && full_eat != philo->philo)
	{
		full_eat = 0;
		usleep (100);
		i = -1;
		while (++i < philo->philo)
		{
			pthread_mutex_lock(philo->mutex);
			alive = check_death(&philo[i]);
			if (alive == 0)
			{
				pthread_mutex_unlock(philo->mutex);
				break ;
			}
			if (philo[i].nb_ate == philo->cycle)
				full_eat++;
			pthread_mutex_unlock(philo->mutex);
		}
	}
}

static void	eat(t_philo *philo)
{
	int	left_fork;

	left_fork = philo->id - 1;
	if (philo->id == 0)
		left_fork = philo->philo - 1;
	pthread_mutex_lock(&philo->fork[philo->id]);
	print_action(philo, "has taken a fork.");
	pthread_mutex_lock(&philo->fork[left_fork]);
	print_action(philo, "has taken a fork.");
	print_action(philo, "is eating.");
	pthread_mutex_lock(philo->mutex);
	philo->starving_time = get_time();
	pthread_mutex_unlock(philo->mutex);
	ft_sleep(philo->eatime);
	pthread_mutex_unlock(&philo->fork[philo->id]);
	pthread_mutex_unlock(&philo->fork[left_fork]);
	print_action(philo, "is sleeping.");
	ft_sleep(philo->sleeptime);
	pthread_mutex_lock(philo->mutex);
	philo->nb_ate++;
	pthread_mutex_unlock(philo->mutex);
	print_action(philo, "is thinking.");
}

void	*routine(void *arg)
{
	t_philo			*philo;
	int				dead;

	dead = 0;
	philo = (t_philo *) arg;
	if (philo->id % 2)
		ft_sleep((philo->philo + 40) / 40);
	while (philo->nb_ate != philo->cycle && !dead)
	{
		eat(philo);
		pthread_mutex_lock(philo->mutex);
		dead = philo->dead[0];
		pthread_mutex_unlock(philo->mutex);
	}
	return (NULL);
}
