/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_lifespan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:53:38 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/15 09:41:39 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_eats(t_philos *philo)
{
	sem_wait(philo->data->forks);
	philo_does(philo, philo->id, "has taken a fork");
	sem_wait(philo->data->forks);
	philo_does(philo, philo->id, "has taken a fork");
	philo->time_last_eat = timestamp();
	philo_does(philo, philo->id, "is eating");
	s_sleep(philo->data->time_to_eat, philo->data);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	philo->ate++;
}

static void	life_journey(t_philos *philo)
{
	while (!philo->dead_phil && philo->ate != philo->data->nb_must_eat)
	{
		philo_eats(philo);
		philo_does(philo, philo->id, "is sleeping");
		s_sleep(philo->data->time_to_sleep, philo->data);
		philo_does(philo, philo->id, "is thinking");
	}
}

void	*philos_lifespan(t_data *data, int i)
{
	t_philos	philo;

	philo.data = data;
	philo.id = i + 1;
	philo.dead_phil = 0;
	philo.ate = 0;
	philo.time_last_eat = timestamp();
	pthread_create(philo.philo_thread, NULL, (void *)dead_check, &philo);
	life_journey(&philo);
	pthread_detach(*philo.philo_thread);
	return (NULL);
}
