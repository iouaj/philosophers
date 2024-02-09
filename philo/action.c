/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:37:50 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/09 17:24:49 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mutex);
	print_action(philo, 1);
	pthread_mutex_lock(&philo->r_fork->mutex);
	print_action(philo, 1);
	print_action(philo, 2);
	usleep(philo->env->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->l_fork->mutex);
	pthread_mutex_unlock(&philo->r_fork->mutex);
	gettimeofday(&philo->last, NULL);
	if (philo->env->number_of_times_each_philo_must_eat != -1)
		philo->count_eat++;
}

void	sleeping(t_philo *philo)
{
	print_action(philo, 3);
	usleep(philo->env->time_to_sleep * 1000);
}
