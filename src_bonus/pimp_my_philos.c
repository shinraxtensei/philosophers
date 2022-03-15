/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pimp_my_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:55:27 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/15 09:42:50 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	init_semaphores(t_data *data)
{
	sem_unlink("philo_forks");
	sem_unlink("philo_action");
	sem_unlink("philo_eat");
	data->forks = sem_open("philo_forks", O_CREAT, 0700, data->nb_philos);
	data->action = sem_open("philo_action", O_CREAT, 0700, 1);
	data->eat = sem_open("philo_eat", O_CREAT, 0700, 1);
	if (data->forks == SEM_FAILED
		|| data->action == SEM_FAILED
		|| data->eat == SEM_FAILED)
	{
		destroy_philos(data);
		exit(1);
	}
	return (true);
}

int	parse_all(t_data *data, char **av)
{
	data->nb_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->dead = 0;
	data->time_birth = timestamp();
	if (data->nb_philos < 1 || data->time_to_die < 1
		|| data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (false);
	if (av[5])
	{
		data->nb_must_eat = ft_atoi(av[5]);
		if (data->nb_must_eat <= 0)
			return (false);
	}
	else
		data->nb_must_eat = -1;
	if (!init_semaphores(data))
		return (false);
	return (true);
}
