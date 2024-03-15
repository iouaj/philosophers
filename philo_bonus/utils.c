/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:00:09 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/15 18:29:06 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long unsigned int	gettime(t_env *env)
{
	struct timeval		time;
	long unsigned int	res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec - env->start.tv_sec) * 1000
		+ (time.tv_usec - env->start.tv_usec) / 1000;
	return (res);
}

void	print(t_philo *philo, const char *str)
{
	if (someone_dead(philo))
		return ;
	sem_wait(philo->env->message);
	printf("%ld %d %s", gettime(philo->env), philo->id + 1, str);
	sem_post(philo->env->message);
}
