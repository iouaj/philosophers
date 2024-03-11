/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:05:08 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/01 17:52:27 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error(t_env *env, int value)
{
	if (value == 0)
	{
		printf("[Error] Mutex error\n");
		exit(EXIT_FAILURE);
	}
	env->dead = 1;
	if (value == 1)
		printf("[Error] Alloc' error\n");
	else
	{
		destroy_mutex(env);
		free(env->philos);
	}
	exit(EXIT_FAILURE);
}

void	thread_error(t_env *env, int index)
{
	env->dead = 1;
	pthread_mutex_unlock(&env->env_mutex);
	pthread_mutex_lock(&env->print);
	printf("Thread Launch Error\n");
	pthread_mutex_unlock(&env->print);
	while (--index >= 0)
		pthread_join(env->philos[index].thread, NULL);
	error(env, 2);
}

void	destroy_mutex(t_env *env)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&env->print);
	pthread_mutex_destroy(&env->env_mutex);
	while (i < env->number_of_philosophers)
	{
		pthread_mutex_destroy(&env->philos[i].eat_mutex);
		pthread_mutex_destroy(&env->philos[i].r_fork->mutex);
		free(env->philos[i].r_fork);
		i++;
	}
}
