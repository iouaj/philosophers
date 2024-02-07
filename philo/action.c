/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:37:50 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/07 17:48:35 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_data	*d, int id)
{
	struct timeval	current_time;

	pthread_mutex_lock(&d->tab_philo[id].l_fork->mutex);
	gettimeofday(&current_time, NULL);
	printf("%ld %d has taken a fork\n", current_time.tv_usec, id);
	pthread_mutex_lock(&d->tab_philo[id].r_fork->mutex);
	gettimeofday(&current_time, NULL);
	printf("%ld %d has taken a fork\n", current_time.tv_usec, id);
	gettimeofday(&current_time, NULL);
	printf("%ld %d is eating\n", current_time.tv_usec, id);
	usleep(d->env.time_to_eat);
	gettimeofday(&d->tab_philo[id].last, NULL);
	pthread_mutex_unlock(&d->tab_philo[id].l_fork->mutex);
	pthread_mutex_unlock(&d->tab_philo[id].r_fork->mutex);
}

void	sleeping(t_data *d, int id)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	printf("%ld %d is sleeping\n", current_time.tv_usec, id);
	usleep(d->env.time_to_sleep);
}
