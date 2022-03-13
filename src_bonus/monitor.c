#include "philo_bonus.h"

// void	*dead_check(t_philos *philo)
// {
// 	int	i;

// 	while (!(philo->data->all_ate))
// 	{
// 		i = -1;
// 		while (++i < philo->data->nb_philos && !(philo->data->dead))
// 		{
// 			sem_wait(philo->data->eat);
// 			if (m_time(philo[i].time_eat, timestamp()) > philo->data->time_to_die)
// 			{
// 				philo_does(philo->data, i, "died");
// 				philo->data->dead = 1;
// 			}
// 			sem_post(philo->data->eat);
// 			usleep(1000);
// 		}
// 		if (philo->data->dead)
// 			break ;
// 		i = 0;
// 		while ((philo->data->nb_must_eat != -1) && (i < philo->data->nb_philos)
// 			&& (philo[i].ate >= philo->data->nb_must_eat))
// 			i++;
// 		if (i == philo->data->nb_philos)
// 			philo->data->all_ate = 1;
// 	}
// 	return NULL ;
// }

void	*dead_check(t_philos *philo)
{
	long long the_now;
	while (1)
	{
		the_now = timestamp();
		if (philo->ate == philo->data->nb_must_eat)
			return (NULL);
		if (the_now - philo->time_last_eat >= (unsigned long long)philo->data->time_to_die)
		{
			philo->dead_phil = true;
			// sem_wait(philo->data->action);
			philo_does(philo->data, philo->id, "died");
			// sem_post(philo->data->action);
			kill_processes(philo->data);
			destroy_philos(philo->data);
			free(philo->data->pid);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}