/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:40:17 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/01 16:29:24 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_env
{
	pthread_mutex_t	print;
	pthread_mutex_t	env_mutex;
	int				dead;
	struct timeval	start;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	struct s_philo	*philos;
	pthread_t		checker;
}	t_env;

typedef struct s_philo
{
	int					id;
	long unsigned int	last;
	int					eat;
	pthread_mutex_t		eat_mutex;
	pthread_t			thread;
	t_fork				*r_fork;
	t_fork				*l_fork;
	t_env				*env;
}	t_philo;

int					create(pthread_t *thread, void *(*f)(void *), void *arg);
void				thread_error(t_env *env, int index);
void				error(t_env *env, int value);
t_fork				*init_fork(void);
int					main_one(t_env env);
void				print_action(t_philo *philo, int value);
void				destroy_mutex(t_env *env);
void				*checker(void *arg);
void				sleeping(t_philo *philo);
void				eat(t_philo *philo);
int					is_philo_dead(t_env *env);
long unsigned int	gettime(t_env *env);
int					ft_atoi(const char *nptr);
int					end_eat(t_philo *philo);
#endif
