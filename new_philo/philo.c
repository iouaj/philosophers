/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:49:58 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/28 18:36:15 by iouajjou         ###   ########.fr       */
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
	{
		printf("Mutex error\n");
		exit(EXIT_FAILURE);
	}
	env.dead = 0;
	env.philos = malloc(sizeof(t_philo) * env.number_of_philosophers);
	if (!env.philos)
	{
		printf("Malloc error\n");
		pthread_mutex_destroy(&env.print);
		exit(EXIT_FAILURE);
	}
	return (env);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		trigger;

	philo = (t_philo *) arg;
	trigger = 0;
	while (!is_philo_dead(philo->env) && !end_eat(philo))
	{
		print_action(philo, 0);
		if (!trigger && philo->id % 2 == 1)
		{
			usleep(philo->env->time_to_eat);
			trigger = 1;
		}
		eat(philo);
		if (philo->env->number_of_times_each_philosopher_must_eat != -1)
			philo->eat++;
		sleeping(philo);
	}
	return (NULL);
}

t_fork	*init_fork(void)
{
	t_fork *fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		exit(EXIT_FAILURE);
	if (pthread_mutex_init(&fork->mutex, NULL))
		exit(EXIT_FAILURE);
	return (fork);
}

void	launch_philo(t_env *env)
{
	int		i;
	t_fork	*last_fork;

	i = 0;
	last_fork = init_fork();
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
		if (pthread_create(&env->philos[i].thread, NULL, &routine, (void *)&env->philos[i]))
		{
			pthread_mutex_lock(&env->print);
			printf("Thread Launch Error\n");
			while (--i >= 0)
				pthread_join(env->philos[i].thread, NULL);
			pthread_mutex_destroy(&env->print);
			exit(EXIT_FAILURE);
		}
		i++;
	}
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
	pthread_mutex_destroy(&env.print);
	destroy_mutex(&env);
	free(env.philos);
	return (0);
}
