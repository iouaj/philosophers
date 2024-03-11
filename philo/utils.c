/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:55:29 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/11 16:40:06 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//0 = think
//1 = fork;
//2 = eat;
//3 = sleep;
//4 = die;
void	print_action(t_philo *philo, int value)
{
	int	id;

	pthread_mutex_lock(&philo->env->env_mutex);
	if (philo->env->dead)
	{
		pthread_mutex_unlock(&philo->env->env_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->env->env_mutex);
	pthread_mutex_lock(&philo->env->print);
	id = philo->id + 1;
	if (value == 0)
		printf("%ld %d is thinking\n", gettime(philo->env), id);
	else if (value == 1)
		printf("%ld %d has taken a fork\n", gettime(philo->env), id);
	else if (value == 2)
		printf("%ld %d is eating\n", gettime(philo->env), id);
	else if (value == 3)
		printf("%ld %d is sleeping\n", gettime(philo->env), id);
	else
		printf("Error\n");
	pthread_mutex_unlock(&philo->env->print);
}

long unsigned int	gettime(t_env *env)
{
	struct timeval		time;
	long unsigned int	res;

	gettimeofday(&time, NULL);
	res = (time.tv_sec - env->start.tv_sec) * 1000
		+ (time.tv_usec - env->start.tv_usec) / 1000;
	return (res);
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
	pthread_mutex_lock(&philo->eat_mutex);
	if (philo->eat == philo->env->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_unlock(&philo->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_mutex);
	return (0);
}

int	create(pthread_t *thread, void *(*f)(void *), void *arg)
{
	return (pthread_create(thread, NULL, f, arg));
}
