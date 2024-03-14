/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:50:18 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/13 19:14:55 by iouajjou         ###   ########.fr       */
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

typedef struct s_philo
{
	int	id;
	int	eat;
	unsigned long int	last;
	int					dead;
	struct s_env		*env;
}	t_philo;


typedef struct s_env
{
	int	nb_philo;
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	nb_must_eat;
	int	*philos;
	sem_t	*fork;
	sem_t	*message;
	sem_t	*stop;
	struct timeval	start;
	pthread_t	checker;
}	t_env;

void	print(t_philo *philo, const char *str);
void	*check(void *env);
int	ft_atoi(const char *nptr);
void	eat(t_env *e, t_philo *philo);
void	sleeping(t_env *e, t_philo *philo);
long unsigned int	gettime(t_env *env);
#endif
