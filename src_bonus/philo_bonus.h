/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 12:52:41 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/15 09:40:21 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philos {
	int					id;
	int					ate;
	int					dead_phil;
	unsigned long		time_last_eat;
	pthread_t			*philo_thread;
	struct s_data		*data;
}	t_philos;

typedef struct s_data {
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_must_eat;
	int					dead;
	int					*pid;
	unsigned long		time_birth;
	sem_t				*forks;
	sem_t				*action;
	sem_t				*eat;
	t_philos			*philos;
}	t_data;

void			create_processes(t_data *data, int *pid);
void			processes_slayer(t_data *param);
int				parse_all(t_data *data, char **av);
int				init_mutex(t_data *data);
int				init_philos(t_data *data);
int				ft_atoi(const char *str);
int				init_routine(t_data *data);
void			*dead_check(t_philos *philo);
void			destroy_philos(t_data *data);
void			*philos_lifespan(t_data *data, int i);
void			philo_does(t_philos *philo, int id, char *str);	
void			s_sleep(long long time, t_data *data);
unsigned long	timestamp(void);
void			processes_slayer(t_data *param);
#endif
