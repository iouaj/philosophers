/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:50:05 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/22 16:37:04 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static t_env	init_env(int argc, char *argv[])
{
	t_env	e;

	e.nb_philo = ft_atoi(argv[1]);
	e.time_to_die = ft_atoi(argv[2]);
	e.time_to_eat = ft_atoi(argv[3]);
	e.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		e.nb_must_eat = ft_atoi(argv[5]);
	else
		e.nb_must_eat = -1;
	e.philos = malloc(sizeof(t_philo) * e.nb_philo);
	e.pid = malloc(sizeof(int) * e.nb_philo);
	if (!e.philos || !e.pid)
	{
		printf("[Error] Alloc' failed\n");
		exit(EXIT_FAILURE);
	}
	gettimeofday(&e.start, NULL);
	return (e);
}

void	philo(t_env *e, int id)
{
	t_philo	philo;

	philo = e->philos[id];
	philo.sem_eat = sem_open("eat", O_CREAT, 0600, 1);
	if (pthread_create(&e->checker, NULL, &check, &philo))
	{
		sem_wait(philo.env->message);
		printf("[Error] Thread failed\n");
		exit(EXIT_FAILURE);
	}
	print(&philo, "is thinking\n");
	usleep(id % 2 * (e->time_to_eat / 4) * 1000);
	while (!someone_dead(&philo) && philo.eat != philo.env->nb_must_eat)
	{
		eat(e, &philo);
		sleeping(e, &philo);
		print(&philo, "is thinking\n");
	}
	pthread_join(e->checker, NULL);
	sem_close(philo.sem_eat);
}

void	waitall(t_env *e)
{
	int	i;
	int	status;

	i = 0;
	while (i < e->nb_philo)
	{
		waitpid(e->pid[i], &status, WUNTRACED);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_env	e;
	int		pid;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid Arguments\n");
		return (1);
	}
	e = init_env(argc, argv);
	init_sem(&e);
	create_philo(&e);
	pid = create_process(&e);
	if (pid)
		waitall(&e);
	free(e.philos);
	free(e.pid);
	sem_close(e.fork);
	sem_close(e.stop);
	sem_close(e.message);
	sem_close(e.dead);
	return (0);
}
