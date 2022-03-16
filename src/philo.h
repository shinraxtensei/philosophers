/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:47:22 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/16 09:11:10 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>

typedef struct s_philos {
	int					id;
	int					ate;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long long			time_eat;
	pthread_t			philo_thread;
	struct s_data		*data;
}	t_philos;

typedef struct s_data {
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_must_eat;
	int					dead;
	int					all_ate;
	long long			time_birth;

	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		action_mutex;

	t_philos			*philos;
}	t_data;

void			error(int error);
int				pimp_my_philos(t_data *data, char **av);
int				init_mutex(t_data *data);
int				init_philos(t_data *data);
int				threads_creation(t_data *data);
void			*dead_check(t_data *data);
void			destroy_philos(t_data *data, t_philos *philo);
void			*routine(void *void_philo);
void			philo_eats(t_philos *philo);
void			philo_does(t_data *data, int id, char *str);
void			s_sleep(long long time, t_data *data);
void			philo_one(t_philos *philo);
long long		m_time(long long past, long long pres);
long long		timestamp(void);

int				ft_atoi(const char *str);
#endif
