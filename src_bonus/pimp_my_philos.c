#include "philo_bonus.h"


int	init_semaphores(t_data *data)
{
	sem_unlink("/philo_forks");
	sem_unlink("/philo_action");
	sem_unlink("/philo_eat");
	data->forks = sem_open("philo_forks", O_CREAT, 0777, data->nb_philos);
	data->action = sem_open("philo_action", O_CREAT, 0777, 1);
	data->eat = sem_open("philo_eat", O_CREAT, 0777, 1);
	if (data->forks == SEM_FAILED || data->action == SEM_FAILED || data->eat == SEM_FAILED) 
	{
		destroy_philos(data);
		exit(1);
	}
	return (true);
}

void	philo_one(t_philos *philo)
{
	t_data	*data;

	data = philo->data;
	philo_does(data, philo->id, "has taken a fork");
	s_sleep(data->time_to_die, data);
	dead_check(data->philos);
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
	if (!init_semaphores(data))
		return (false);
	return (true);
}