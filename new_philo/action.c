/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:26:43 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/28 18:09:59 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	print_action(philo, 1);
	pthread_mutex_lock(&philo->r_fork->mutex);
	print_action(philo, 1);
	philo->last = gettime(philo->env);
	print_action(philo, 2);
	usleep(philo->env->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_unlock(&philo->r_fork->mutex);
}

void	sleeping(t_philo *philo)
{
	if (philo->env->dead)
		return ;
	print_action(philo, 3);
	usleep(philo->env->time_to_sleep * 1000);
}
