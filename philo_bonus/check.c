/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:12:42 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/16 01:00:23 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *should_stop(void *arg)
{
	t_philo *philo;

	philo = (t_philo *) arg;
	// sem_wait(philo->env->stop)
	// if (philo->env->stop->__align != philo->env->nb_philo)
	// 	philo->dead = 1;
	sem_wait(philo->env->stop);
	philo->dead = 1;
	sem_post(philo->env->stop);
	return (NULL);
}

// int	someone_dead(t_philo *philo)
// {
// 	// printf("%ld ++++++++++++++++\n", philo->env->stop->__align);
// 	if (philo->env->stop->__align != philo->env->nb_philo)
// 	{
// 		printf("%ld ++++++++++++++++++++++++++++++\n", philo->env->stop->__align);
// 		if (philo->env->stop->__align == philo->env->nb_philo - 1)
// 			print(philo, "died\n");
// 		return (1);
// 	}
// 	return (0);
// }

int	someone_dead(t_philo *philo)
{
	return (philo->dead);
}

void *check(void *arg)
{
	t_philo				*philo;
	long unsigned int	to_die;
	pthread_t			check_others;
	int					i;

	philo = (t_philo *) arg;
	to_die = philo->env->time_to_die;
	if (philo->env->nb_philo != 1)
	{
		if (pthread_create(&check_others, NULL, &should_stop, philo))
			exit(EXIT_FAILURE);
	}
	while (!someone_dead(philo))
	{
		sem_wait(philo->env->dead);
		if (!someone_dead(philo) && gettime(philo->env) >= philo->last + to_die)
		{
			print(philo, "died\n");
			i = 0;
			while (i < philo->env->nb_philo)
			{
				sem_post(philo->env->stop);
				i++;
			}
			philo->dead = 1;
		}
		if (philo->eat == philo->env->nb_must_eat)
			philo->dead = 1;
		sem_post(philo->env->dead);
	}
	if (philo->env->nb_philo != 1)
		pthread_detach(check_others);
	return (NULL);
}

