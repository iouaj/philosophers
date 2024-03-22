/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:00:19 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/22 16:42:39 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_one_philo(t_philo *philo)
{
	print(philo, "has taken a fork\n");
	usleep(philo->env->time_to_die * 1000);
}

void	eat(t_env *e, t_philo *philo)
{
	if (someone_dead(philo))
		return ;
	if (philo->env->nb_philo == 1)
		return (eat_one_philo(philo));
	if (someone_dead(philo))
		return ;
	sem_wait(e->fork);
	print(philo, "has taken a fork\n");
	if (someone_dead(philo))
		return ;
	sem_wait(e->fork);
	print(philo, "has taken a fork\n");
	sem_wait(philo->sem_eat);
	philo->last = gettime(e);
	sem_post(philo->sem_eat);
	print(philo, "is eating\n");
	usleep(e->time_to_eat * 1000);
	if (philo->eat != -1)
	{
		sem_wait(philo->sem_eat);
		philo->eat++;
		sem_post(philo->sem_eat);
	}
	sem_post(e->fork);
	sem_post(e->fork);
}

void	sleeping(t_env *e, t_philo *philo)
{
	if (someone_dead(philo))
		return ;
	print(philo, "is sleeping\n");
	if (someone_dead(philo))
		return ;
	usleep(e->time_to_sleep * 1000);
}
