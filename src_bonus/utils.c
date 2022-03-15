/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:58:41 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/15 10:02:40 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

unsigned long	timestamp(void)
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

void	philo_does(t_philos *philo, int id, char *str)
{
	sem_wait(philo->data->action);
	if (!(philo->data->dead))
	{
		printf("(%lu)\t ", timestamp() - philo->data->time_birth);
		printf("philo %i ", id);
		printf("%s\n", str);
	}
	sem_post(philo->data->action);
	return ;
}
