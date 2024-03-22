/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:27:07 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/22 16:25:03 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_env *e)
{
	sem_unlink("fork");
	sem_unlink("message");
	sem_unlink("stop");
	sem_unlink("dead");
	sem_unlink("eat");
	e->fork = sem_open("fork", O_CREAT, 0600, e->nb_philo);
	e->message = sem_open("message", O_CREAT, 0600, 1);
	e->stop = sem_open("stop", O_CREAT, 0600, e->nb_philo);
	e->dead = sem_open("dead", O_CREAT, 0600, 1);
}

void	create_philo(t_env *e)
{
	int	i;

	i = 0;
	while (i < e->nb_philo)
	{
		e->philos[i] = init_philo(e, i);
		i++;
	}
}

t_philo	init_philo(t_env *e, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.eat = 0;
	if (e->nb_must_eat == -1)
		philo.eat = -1;
	philo.eat = 0;
	philo.env = e;
	philo.last = gettime(e);
	return (philo);
}

int	create_process(t_env *e)
{
	int	pid;
	int	i;

	i = 0;
	while (i < e->nb_philo)
	{
		pid = fork();
		if (!pid)
		{
			philo(e, i);
			break ;
		}
		e->pid[i] = pid;
		i++;
	}
	return (pid);
}
