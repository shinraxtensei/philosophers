/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 11:16:59 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/16 10:35:19 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dead_check(t_data *data)
{
	int				i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			if (data->philos[i].ate == data->nb_must_eat)
				exit(1);
			if (timestamp() - (unsigned long)data->philos[i].time_eat
				> (unsigned long)data->time_to_die)
			{
				data->dead = 1;
				pthread_mutex_lock(&data->action_mutex);
				printf("\033[0;31m%d died time: %lld\n",
					i + 1, timestamp() - (unsigned long)data->time_birth);
				exit(1);
			}
		}
	}
	return (NULL);
}
