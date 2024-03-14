/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:00:19 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/13 19:22:05 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_env *e, t_philo *philo)
{
	sem_wait(e->fork);
	print(philo, "has taken fork\n");
	sem_wait(e->fork);
	print(philo, "has taken fork\n");
	philo->last = gettime(e);
	print(philo, "is eating\n");
	usleep(e->time_to_eat * 1000);
	if (philo->eat != -1)
		philo->eat++;
	sem_post(e->fork);
	sem_post(e->fork);
}

void	sleeping(t_env *e, t_philo *philo)
{
	print(philo, "is sleeping\n");
	usleep(e->time_to_sleep * 1000);
}
