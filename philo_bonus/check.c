/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:12:42 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/22 16:34:38 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	someone_dead(t_philo *philo)
{
	if (philo->env->stop->__align != philo->env->nb_philo)
		return (1);
	return (0);
}

void	*check(void *arg)
{
	t_philo				*philo;
	long unsigned int	to_die;

	philo = (t_philo *) arg;
	to_die = philo->env->time_to_die;
	while (!someone_dead(philo))
	{
		sem_wait(philo->env->dead);
		sem_wait(philo->sem_eat);
		if (!someone_dead(philo) && gettime(philo->env) >= philo->last + to_die)
		{
			print(philo, "died\n");
			sem_wait(philo->env->stop);
		}
		if (philo->eat == philo->env->nb_must_eat)
		{
			sem_post(philo->sem_eat);
			sem_post(philo->env->dead);
			return (NULL);
		}
		sem_post(philo->sem_eat);
		sem_post(philo->env->dead);
	}
	return (NULL);
}
