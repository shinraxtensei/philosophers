/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:50:05 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/15 09:39:26 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*dead_check(t_philos *philo)
{
	unsigned long	the_now;

	while (1)
	{
		the_now = timestamp();
		if (philo->ate == philo->data->nb_must_eat)
			return (NULL);
		if (the_now - philo->time_last_eat >= \
				(unsigned long long)philo->data->time_to_die)
		{
			philo->dead_phil = 1;
			sem_wait(philo->data->action);
			printf("\033[0;31m(%lu)\t philo %d died\n",
				the_now - philo->data->time_birth, philo->id);
			processes_slayer(philo->data);
			destroy_philos(philo->data);
			free(philo->data->pid);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}
