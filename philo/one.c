/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:30:02 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/11 17:57:15 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*init_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		exit(EXIT_FAILURE);
	if (pthread_mutex_init(&fork->mutex, NULL))
		exit(EXIT_FAILURE);
	return (fork);
}

void	*one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!is_philo_dead(philo->env))
	{
		print_action(philo, 0);
		eat(philo);
		if (philo->env->number_of_times_each_philosopher_must_eat != -1)
		{
			pthread_mutex_lock(&philo->eat_mutex);
			philo->eat++;
			pthread_mutex_unlock(&philo->eat_mutex);
		}
		sleeping(philo);
	}
	return (NULL);
}

static void	launch_thread(t_env *env)
{
	env->philos[0].id = 0;
	env->philos[0].env = env;
	env->philos[0].eat = 0;
	env->philos[0].last = gettime(env);
	if (pthread_mutex_init(&env->philos[0].eat_mutex, NULL))
		exit(EXIT_FAILURE);
	if (create(&env->philos[0].thread, &one, (void *)&(env->philos[0])))
		exit(EXIT_FAILURE);
}

int	main_one(t_env env)
{
	launch_thread(&env);
	if (create(&env.checker, &checker, &env))
		exit(EXIT_FAILURE);
	pthread_join(env.philos[0].thread, NULL);
	pthread_join(env.checker, NULL);
	free(env.philos);
	return (1);
}
