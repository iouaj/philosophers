/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:52:51 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/11 16:48:47 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checker(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (is_philo_dead(env) == 0)
	{
		usleep(10);
	}
	return (NULL);
}

static void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->print);
	printf("%ld %d died\n", gettime(philo->env), philo->id);
	pthread_mutex_unlock(&philo->env->print);
	pthread_mutex_unlock(&philo->eat_mutex);
}

static int	dead(t_env *e)
{
	int					i;
	int					count;
	long unsigned int	to_die;

	i = 0;
	count = 0;
	to_die = (long unsigned int)e->time_to_die;
	while (i < e->number_of_philosophers)
	{
		pthread_mutex_lock(&e->philos[i].eat_mutex);
		if (e->philos[i].eat != e->number_of_times_each_philosopher_must_eat)
		{
			if (gettime(e) - e->philos[i].last >= to_die)
			{
				e->dead = 1;
				print_dead(&e->philos[i]);
				return (-1);
			}
		}
		else
			count++;
		pthread_mutex_unlock(&e->philos[i].eat_mutex);
		i++;
	}
	return (count);
}

int	is_philo_dead(t_env *env)
{
	int	count;

	pthread_mutex_lock(&env->env_mutex);
	if (env->dead)
	{
		pthread_mutex_unlock(&env->env_mutex);
		return (1);
	}
	count = dead(env);
	pthread_mutex_unlock(&env->env_mutex);
	if (count == env->number_of_philosophers)
		return (2);
	if (count == -1)
		return (1);
	return (0);
}
