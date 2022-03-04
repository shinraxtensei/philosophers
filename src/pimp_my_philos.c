/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pimp_my_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:46:53 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/04 10:01:44 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_malloc(void *dst, size_t size)
{
	*(void **)dst = malloc(size);
	if (*(void **)dst == NULL)
		return (1);
	memset(*(void **)dst, 0, size);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = data->nb_philos;
	ft_malloc(&data->philos, sizeof(t_philos) * data->nb_philos);
	while (--i >= 0)
	{
		data->philos[i].id = i;
		data->philos[i].ate = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->nb_philos;
		data->philos[i].time_eat = 0;
		data->philos[i].data = data;
	}
	return (true);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = data->nb_philos;
	ft_malloc(&data->fork_mutex, sizeof(pthread_mutex_t) * data->nb_philos);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&data->fork_mutex[i], NULL) != 0)
			return (false);
	}
	if (pthread_mutex_init(&data->action_mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->eat_mutex, NULL) != 0)
		return (false);
	return (true);
}

int	parse_all(t_data *data, char **av)
{
	data->nb_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->dead = 0;
	data->all_ate = 0;
	if (data->nb_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 0
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
	if (!init_mutex(data))
		return (false);
	if (!init_philos(data))
		return (false);
	return (true);
}