/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:38:00 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/09 17:42:43 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long unsigned int	gettime(t_philo *philo)
{
	struct timeval		time;
	long unsigned int	res;

	gettimeofday(&time, NULL);
	res = ((time.tv_sec - philo->env->start.tv_sec) * 1000000 + time.tv_usec)
		- philo->env->start.tv_usec;
	return (res / 1000);
}

//0 = think
//1 = fork;
//2 = eat;
//3 = sleep;
//4 = die;
void	print_action(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->env->print_mutex);
	if (value == 0)
		printf("\x1B[36m%ld %d is thinking\n\x1B[0m", gettime(philo), philo->id);
	else if (value == 1)
		printf("%ld %d has taken a fork\n", gettime(philo), philo->id);
	else if (value == 2)
		printf("\x1B[32m%ld %d is eating\n\x1B[0m", gettime(philo), philo->id);
	else if (value == 3)
		printf("\x1B[34m%ld %d is sleeping\n\x1B[0m", gettime(philo), philo->id);
	else if (value == 4)
		printf("\x1B[31m%ld %d died\n\x1B[0m", gettime(philo), philo->id);
	else
		printf("Error\n");
	pthread_mutex_unlock(&philo->env->print_mutex);
}
