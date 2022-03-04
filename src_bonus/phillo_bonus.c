#include "philo_bonus.h"

void	error(int error)
{
	if (error == 1)
		printf("Wrong amount of args.\n");
	else if (error == 2)
		printf("Error while parsing.\n");
	else if (error == 3)
		printf("Error while creating threads.\n");
	return ;
}

void	destroy_philos(t_data *data, t_philos *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_join(philo[i].philo_thread, NULL);
	sem_close(data->forks);
	sem_close(data->action);
	sem_close(data->eat);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_action");
	sem_unlink("/philo_eat");
}

int	init_routine(t_data *data)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = data->philos;
	data->time_birth = timestamp();
	while (i < data->nb_philos)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, &routine, &philo[i]))
			return (false);
		philo[i].time_eat = timestamp();
		i++;
	}
	dead_check(data, data->philos);
	destroy_philos(data, philo);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (error(1), false);
	if (!(parse_all(&data, av)))
		return (error(2), false);
	if (!(init_routine(&data)))
		return (error(3), false);
	return (true);
}