/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_lifespan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 11:16:48 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/06 08:55:52 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_one(t_philos *philo)
{
	t_data	*data;

	data = philo->data;
	philo_does(data, philo->id, "has taken a fork");
	s_sleep(data->time_to_die, data);
	dead_check(data, data->philos);
}

void	philo_eats(t_philos *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->nb_philos == 1)
		philo_one(philo);
	else
	{
		pthread_mutex_lock(&data->fork_mutex[philo->left_fork]);
		philo_does(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->fork_mutex[philo->right_fork]);
		philo_does(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->eat_mutex);
		philo_does(data, philo->id, "is eating");
		philo->time_eat = timestamp();
		pthread_mutex_unlock(&data->eat_mutex);
		s_sleep(data->time_to_eat, data);
		(philo->ate)++;
		pthread_mutex_unlock(&data->fork_mutex[philo->left_fork]);
		pthread_mutex_unlock(&data->fork_mutex[philo->right_fork]);
	}
}

void	*routine(void *void_philo)
{
	t_philos	*philo;
	t_data		*data;

	philo = (struct s_philos *)void_philo;
	data = philo->data;
	// if (philo->id % 2)
	// 	usleep(20000);
	while (!(data->dead) && !(data->all_ate))
	{
		philo_eats(philo);
		// if (data->all_ate)
		// 	break ;
		philo_does(data, philo->id, "is sleeping");
		s_sleep(data->time_to_sleep, data);
		philo_does(data, philo->id, "is overthinking");

	}
	return (NULL);
}