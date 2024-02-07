/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:52:27 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/07 17:46:18 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_fork {
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_env {
	struct timeval	start;
	int			nb_philo;
	int			time_to_die;//in ms
	int			time_to_eat;// in ms
	int			time_to_sleep;// in ms
	int			number_of_times_each_philo_must_eat;
}	t_env;


typedef struct	s_philo {
	int				id;
	pthread_t		thread;
	int				status;
	struct timeval	last;
	t_fork			*r_fork;
	t_fork			*l_fork;
	t_env			env;
}	t_philo;


typedef struct s_data {
	t_env		env;
	t_philo		*tab_philo;
}	t_data;

int	ft_atoi(const char *nptr);
//exit.c
void	error(t_data *d);
void	freeall(t_data *d);
//action.c
void	eat(t_data	*d, int id);
//utils.c
long unsigned int	gettime(t_philo *philo);
#endif
