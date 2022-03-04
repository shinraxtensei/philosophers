#include "philo_bonus.h"

void	dead_check(t_data *data, t_philos *philo)
{
	int	i;

	while (!(data->all_ate))
	{
		i = -1;
		while (++i < data->nb_philos && !(data->dead))
		{
			sem_wait(data->eat);
			if (m_time(philo[i].time_eat, timestamp()) > data->time_to_die)
			{
				philo_does(data, i, "died");
				data->dead = 1;
			}
			sem_post(data->eat);
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