/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:26:43 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/11 17:57:03 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_last_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	print_action(philo, 1);
	pthread_mutex_lock(&philo->r_fork->mutex);
	print_action(philo, 1);
	pthread_mutex_lock(&philo->env->env_mutex);
	philo->last = gettime(philo->env);
	pthread_mutex_unlock(&philo->env->env_mutex);
	print_action(philo, 2);
	usleep(philo->env->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	pthread_mutex_unlock(&philo->l_fork->mutex);
}

void	eat(t_philo *philo)
{
	if (philo->env->number_of_philosophers == 1)
	{
		print_action(philo, 1);
		usleep(philo->env->time_to_die * 1000);
		return ;
	}
	if (philo->env->number_of_philosophers -1 == philo->id)
	{
		eat_last_philo(philo);
		return ;
	}
	pthread_mutex_lock(&philo->r_fork->mutex);
	print_action(philo, 1);
	pthread_mutex_lock(&philo->l_fork->mutex);
	print_action(philo, 1);
	pthread_mutex_lock(&philo->env->env_mutex);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last = gettime(philo->env);
	pthread_mutex_unlock(&philo->eat_mutex);
	pthread_mutex_unlock(&philo->env->env_mutex);
	print_action(philo, 2);
	usleep(philo->env->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_unlock(&philo->r_fork->mutex);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->env_mutex);
	if (philo->env->dead)
	{
		pthread_mutex_unlock(&philo->env->env_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->env->env_mutex);
	print_action(philo, 3);
	usleep(philo->env->time_to_sleep * 1000);
}
