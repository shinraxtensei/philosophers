#include "philo_bonus.h"

void	life_journey(t_philos *philo)
{
	while (!philo->dead_phil && philo->ate != philo->data->nb_must_eat)
	{
		philo_eats(philo);
		// sem_wait(philo->data->action);
		philo_does(philo->data, philo->id, "is sleeping");
		// sem_post(philo->data->action);
		s_sleep(philo->data->time_to_sleep, philo->data);
		// sem_wait(philo->data->action);
		philo_does(philo->data, philo->id, "is thinking");
		// sem_post(philo->data->action);
	}
}

void	philo_eats(t_philos *philo)
{
		sem_wait(philo->data->forks);
		// sem_wait(philo->data->action);
		philo_does(philo->data, philo->id, "has taken a fork");
		// sem_post(philo->data->action);
		sem_wait(philo->data->forks);
		// sem_wait(philo->data->action);
		philo_does(philo->data, philo->id, "has taken a fork");
		// sem_post(philo->data->action);
		sem_wait(philo->data->eat);
		// sem_wait(philo->data->action);
		philo_does(philo->data, philo->id, "is eating");
		// sem_post(philo->data->action);
		philo->time_eat = timestamp();
		sem_post(philo->data->eat);
		s_sleep(philo->data->time_to_eat, philo->data);
		(philo->ate)++;
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
}

void	*philos_lifespan(t_data *data, int i)
{
	t_philos	philo;

	philo.data = data;
	philo.id = i + 1;
	philo.dead_phil = 0;
	philo.ate = 0;
	philo.time_last_eat = timestamp();
	pthread_create(philo.philo_thread, NULL, (void *)dead_check, &philo);	
	life_journey(&philo);
	pthread_detach(*philo.philo_thread);
	return (NULL);
}