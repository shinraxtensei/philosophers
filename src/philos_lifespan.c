/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_lifespan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 11:16:48 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/16 10:40:34 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_does(philo->data, philo->id, "has taken a fork\n");
	pthread_mutex_lock(philo->right_fork);
	philo_does(philo->data, philo->id, "has taken a fork\n");
	philo_does(philo->data, philo->id, "is eating\n");
	philo->time_eat = timestamp();
	s_sleep(philo->data->time_to_eat, philo->data);
	(philo->ate)++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *void_philo)
{
	t_philos	*philo;

	philo = (struct s_philos *)void_philo;
	philo->time_eat = timestamp();
	while (!(philo->data->dead) && philo->data->nb_must_eat != philo->ate)
	{
		philo_eats(philo);
		philo_does(philo->data, philo->id, "is sleeping\n");
		s_sleep(philo->data->time_to_sleep, philo->data);
		philo_does(philo->data, philo->id, "is overthinking\n");
	}
	return (NULL);
}
