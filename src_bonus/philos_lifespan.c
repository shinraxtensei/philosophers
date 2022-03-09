#include "philo_bonus.h"

void	philo_eats(t_philos *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->nb_philos == 1)
		philo_one(philo);
	else
	{
		sem_wait(data->forks);
		philo_does(data, philo->id, "has taken a fork");
		sem_wait(data->forks);
		philo_does(data, philo->id, "has taken a fork");
		sem_wait(data->eat);
		philo_does(data, philo->id, "is eating");
		philo->time_eat = timestamp();
		sem_post(data->eat);
		s_sleep(data->time_to_eat, data);
		(philo->ate)++;
		sem_post(data->forks);
		sem_post(data->forks);
	}
}
void	*philos_lifespan(void *void_philo)
{
	t_philos	*philo;
	t_data		*data;


	philo = (struct s_philos *)void_philo;
	data = philo->data;
	while (!(data->dead))
	{
		philo_eats(philo);
		if (data->all_ate)
			break ;
		philo_does(data, philo->id, "is sleeping");
		s_sleep(data->time_to_sleep, data);
		philo_does(data, philo->id, "is thinking");
	}
	return (NULL);
}