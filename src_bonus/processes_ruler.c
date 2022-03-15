/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_ruler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:58:01 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/15 09:18:23 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_processes(t_data *data, int *pid)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			philos_lifespan(data, i);
		i++;
	}
}

void	processes_slayer(t_data *param)
{
	int	i;

	i = 0;
	while (i < param->nb_philos)
	{
		kill(param->pid[i], SIGINT);
		i++;
	}
}
