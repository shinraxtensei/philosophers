/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pimp_my_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:46:53 by ahouari           #+#    #+#             */
/*   Updated: 2022/02/27 11:09:08 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  args_checker(int ac, char **av)
{
	int  i;
	
	i = 1;
	if (ac != 5 && ac != 6)
	{
		printf("\033[0;31m --> invalide args\n");
		return (1);
	}
	while (av[i])
	{
		if (!is_digit(av[i]) )
		{
			printf("\033[0;31m --> invalide args \n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	philos_creator(t_info *info)
{
	int		i;

	pthread_mutex_init(&info->finish_mutex, NULL);
	if (ft_malloc(&info->philos, sizeof(t_philo) * info->num_of_philo) || \
		ft_malloc(&info->forks, sizeof(pthread_mutex_t) * info->num_of_philo))
		return (printf("ERROR: malloc failed\n"));
	i = 0;
	while (i < info->num_of_philo)
	{
		info->philos[i].n = i;
		pthread_mutex_init(&info->forks[i], NULL);
		pthread_mutex_init(&info->philos[i].check_mutex, NULL);
		if (i == 0)
			info->philos[i].left = &info->forks[info->num_of_philo - 1];
		else
			info->philos[i].left = &info->forks[i - 1];
		info->philos[i].right = &info->forks[i];
		info->philos[i].info = info;
		++i;
	}
	return (0);
}

static void args_init(t_info *info, int ac, char **av)
{
 	info->num_of_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->num_of_must_eat = ft_atoi(av[5]);
}


int pimp_my_philos(t_info *info ,int ac ,char **av)
{
    if (args_checker(ac , av))
        return (1);
	args_init(info , ac , av);
	if(philos_creator(info))
		return (1);
	return (0);
}
