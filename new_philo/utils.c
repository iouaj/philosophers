/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:55:29 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/28 18:19:23 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->number_of_philosophers)
	{
		pthread_mutex_destroy(&env->philos[i].r_fork->mutex);
		free(env->philos[i].r_fork);
		i++;
	}
}

//0 = think
//1 = fork;
//2 = eat;
//3 = sleep;
//4 = die;
void	print_action(t_philo *philo, int value)
{
	if (is_philo_dead(philo->env))
		return ;
	pthread_mutex_lock(&philo->env->print);
	if (value == 0)
		printf("\x1B[36m%ld %d is thinking\n\x1B[0m", gettime(philo->env), philo->id);
	else if (value == 1)
		printf("%ld %d has taken a fork\n", gettime(philo->env), philo->id);
	else if (value == 2)
		printf("\x1B[32m%ld %d is eating\n\x1B[0m", gettime(philo->env), philo->id);
	else if (value == 3)
		printf("\x1B[34m%ld %d is sleeping\n\x1B[0m", gettime(philo->env), philo->id);
	// else if (value == 4)
	// 	printf("\x1B[31m%ld %d died\n\x1B[0m", gettime(philo->env), philo->id);
	else
		printf("Error\n");
	pthread_mutex_unlock(&philo->env->print);
}

long unsigned int	gettime(t_env *env)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec - env->start.tv_sec) * 1000 + (time.tv_usec - env->start.tv_usec) / 1000);
}

pthread_mutex_t	*init_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = NULL;
	if (pthread_mutex_init(mutex, NULL))
		return (NULL);
	return (mutex);
}

int	end_eat(t_philo *philo)
{
	if (philo->eat == philo->env->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}
