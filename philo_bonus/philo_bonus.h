/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:50:18 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/22 16:26:36 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/types.h>
# include <string.h>

typedef struct s_philo
{
	int					id;
	int					eat;
	long unsigned int	last;
	struct s_env		*env;
	sem_t				*sem_eat;
}	t_philo;

typedef struct s_env
{
	int				nb_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				nb_must_eat;
	t_philo			*philos;
	int				*pid;
	sem_t			*fork;
	sem_t			*message;
	sem_t			*stop;
	sem_t			*dead;
	struct timeval	start;
	pthread_t		checker;
}	t_env;

void				philo(t_env *e, int id);
int					create_process(t_env *e);
void				create_philo(t_env *e);
t_philo				init_philo(t_env *e, int id);
void				init_sem(t_env *e);
int					someone_dead(t_philo *philo);
void				print(t_philo *philo, const char *str);
void				*check(void *env);
int					ft_atoi(const char *nptr);
void				eat(t_env *e, t_philo *philo);
void				sleeping(t_env *e, t_philo *philo);
long unsigned int	gettime(t_env *env);
#endif
