/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:52:51 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/28 18:29:42 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checker(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (!is_philo_dead(env))
	{
		usleep(10);
	}
	return (NULL);
}

int is_philo_dead(t_env *env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < env->number_of_philosophers)
	{
		if (env->dead)
			return (1);
		if (env->philos[i].eat != env->number_of_times_each_philosopher_must_eat)
		{
			if (gettime(env) - env->philos[i].last >= (long unsigned int)env->time_to_die)
			{
				env->dead = 1;
				pthread_mutex_lock(&env->print);
				printf("\x1B[31m%ld %d died\n\x1B[0m", gettime(env), env->philos[i].id);
				pthread_mutex_unlock(&env->print);
				return (1);
			}
		}
		else
			count++;
		i++;
	}
	if (count == env->number_of_philosophers)
		return (2);
	return (0);
}
