/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:49:58 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/13 12:34:34 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_env	init_env(int argc, char *argv[])
{
	t_env	env;

	env.number_of_philosophers = ft_atoi(argv[1]);
	env.time_to_die = ft_atoi(argv[2]);
	env.time_to_eat = ft_atoi(argv[3]);
	env.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		env.number_of_times_each_philosopher_must_eat = -1;
	gettimeofday(&env.start, NULL);
	if (pthread_mutex_init(&env.print, NULL))
		error(&env, 0);
	if (pthread_mutex_init(&env.env_mutex, NULL))
		error(&env, 0);
	env.dead = 0;
	env.philos = malloc(sizeof(t_philo) * env.number_of_philosophers);
	if (!env.philos)
		error(&env, 1);
	return (env);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	print_action(philo, 0);
	usleep(philo->id % 2 * (philo->env->time_to_eat * 1000) / 4);
	pthread_mutex_lock(&philo->env->env_mutex);
	while (!philo->env->dead && !end_eat(philo))
	{
		pthread_mutex_unlock(&philo->env->env_mutex);
		eat(philo);
		if (philo->env->number_of_times_each_philosopher_must_eat != -1)
		{
			pthread_mutex_lock(&philo->eat_mutex);
			philo->eat++;
			pthread_mutex_unlock(&philo->eat_mutex);
		}
		sleeping(philo);
		print_action(philo, 0);
		if (philo->env->number_of_philosophers % 2 == 1
			&& philo->env->time_to_eat >= philo->env->time_to_sleep)
			usleep(philo->env->time_to_eat * 1000);
		pthread_mutex_lock(&philo->env->env_mutex);
	}
	pthread_mutex_unlock(&philo->env->env_mutex);
	return (NULL);
}

void	launch_thread(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->number_of_philosophers)
	{
		if (create(&env->philos[i].thread, &routine, (void *)&env->philos[i]))
			thread_error(env, i);
		i++;
	}
}

void	launch_philo(t_env *env)
{
	int		i;
	t_fork	*last_fork;

	i = 0;
	last_fork = init_fork();
	pthread_mutex_lock(&env->env_mutex);
	while (env->number_of_philosophers > i)
	{
		env->philos[i].id = i;
		env->philos[i].env = env;
		env->philos[i].l_fork = last_fork;
		env->philos[i].eat = 0;
		if (env->number_of_philosophers == i + 1)
			env->philos[i].r_fork = env->philos[0].l_fork;
		else
			env->philos[i].r_fork = init_fork();
		last_fork = env->philos[i].r_fork;
		env->philos[i].last = gettime(env);
		if (pthread_mutex_init(&env->philos[i].eat_mutex, NULL))
			exit(EXIT_FAILURE);
		i++;
	}
	launch_thread(env);
	pthread_mutex_unlock(&env->env_mutex);
}

int	main(int argc, char *argv[])
{
	t_env	env;
	int		i;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid Arguments\n");
		return (1);
	}
	env = init_env(argc, argv);
	if (env.number_of_philosophers == 1)
		return (main_one(env));
	launch_philo(&env);
	if (pthread_create(&env.checker, NULL, &checker, &env))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < env.number_of_philosophers)
	{
		pthread_join(env.philos[i].thread, NULL);
		i++;
	}
	pthread_join(env.checker, NULL);
	destroy_mutex(&env);
	free(env.philos);
	return (0);
}
