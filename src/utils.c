/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:52:37 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/14 17:44:09 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (-1);
	return (result);
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + t.tv_usec / 1000);
}

long long	m_time(long long past, long long pres)
{
	return (pres - past);
}

void	s_sleep(long long time, t_data *data)
{
	long long	i;

	i = timestamp();
	while (!(data->dead))
	{
		if (m_time(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	philo_does(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&data->action_mutex);
	if (!(data->dead))
	{
		printf("(%lli)\t ", timestamp() - data->time_birth);
		printf("philo %i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&data->action_mutex);
	return ;
}
