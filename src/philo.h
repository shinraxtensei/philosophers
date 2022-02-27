/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:47:22 by ahouari           #+#    #+#             */
/*   Updated: 2022/02/27 11:10:53 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				n;
	int				num_of_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	check_mutex;
	pthread_t		thread;
	struct s_info	*info;
	struct timeval	last_time_to_eat;

}					t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				num_of_eat_finish_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_must_eat;
	int				finish;
	pthread_mutex_t	finish_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	struct timeval	create_at;
}			t_info;



// typedef struct philo
// {
	
// 	int meals_eaten;
// 	pthread_mutex_t fork;
// 	pthread_t 		thread; 
// } t_philo;

// typedef struct s_info
// {
// 	int				num_of_philo;
// 	int				num_of_eat_finish_philo;
// 	int				time_to_die;
// 	int				time_to_eat;
// 	int				time_to_sleep;
// 	int				num_of_must_eat;
// 	int				finish;
// 	pthread_mutex_t	finish_mutex;
// 	t_philo			*philos;
// 	struct timeval	create_at;
// }			t_info;


// ******************** pimp my philos ****************************

int pimp_my_philos(t_info *info ,int ac ,char **av);


// ******************** philo life span ****************************
void	*philos_life(void *argv);

// ************************ monitor *******************************

void	*monitor(void *argv);
void	*monitor_each_must_eat(void *argv);

// ************************* utils ********************************

int	ft_atoi(const char *nptr);
int	is_digit(char *str);
int	ft_malloc(void *dst, size_t size);
long long	time_to_ms(struct timeval now);
void	print_philo_msg(t_philo *philo, char *str);
#endif