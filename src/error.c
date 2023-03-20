/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtin <mcourtin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:15:20 by mcourtin          #+#    #+#             */
/*   Updated: 2023/03/13 17:14:35 by mcourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	negative_error(char *str)
{
	printf("Error\n[%s] is a negative number.\n", str);
	return (-1);
}

int	bad_input(char *str, char *msg)
{
	printf("Error\n[%s] %s.\n", str, msg);
	return (-1);
}

int	max_value_error(char *str)
{
	printf("Error\n[%s] is bigger than max int.\n", str);
	return (-2);
}

int	create_thread_error(int i)
{
	printf("Error\nproblem while creating %dth thread \n", i);
	return (-3);
}

int	join_thread_error(int i)
{
	printf("Error\nproblem while joining %dth thread \n", i);
	return (-4);
}
