/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 11:16:59 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/04 08:49:50 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_check(t_data *data, t_philos *philo)
{
	int	i;

	while (!(data->all_ate))
	{
		i = -1;
		while (++i < data->nb_philos && !(data->dead))
		{
			pthread_mutex_lock(&data->eat_mutex);
			if (m_time(philo[i].time_eat, timestamp()) > data->time_to_die)
			{
				philo_does(data, i, "died");
				data->dead = 1;
			}
			pthread_mutex_unlock(&data->eat_mutex);
			usleep(1000);
		}
		if (data->dead)
			break ;
		i = 0;
		while ((data->nb_must_eat != -1) && (i < data->nb_philos)
			&& (philo[i].ate >= data->nb_must_eat))
			i++;
		if (i == data->nb_philos)
			data->all_ate = 1;
	}
}