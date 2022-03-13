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

static void	create_processes(t_data *data, int *pid)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			philos_lifespan(data , i);
		i++;
	}
}

void	kill_processes(t_data *param)
{
	int	i;

	i = 0;
	while (i < param->nb_philos)
	{
		kill(param->pid[i], SIGINT);
		i++;
	}
}

void	destroy_philos(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->action);
	sem_close(data->eat);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_action");
	sem_unlink("/philo_eat");
}

int	init_routine(t_data *data)
{
	int		i;

	i = 0;
	data->time_birth = timestamp();
	data->pid = malloc(sizeof(int) * data->nb_philos);
	if (!data->pid)
		exit(1);
	create_processes(data, data->pid);
	while (i < data->nb_philos)
	{
		waitpid(data->pid[i++], 0, 0);
	}
	kill_processes(data);
	destroy_philos(data);
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