/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:50:05 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/13 19:35:47 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_env *e)
{
	sem_unlink("fork");
	sem_unlink("message");
	sem_unlink("stop");
	e->fork = sem_open("fork", O_CREAT, 0600, e->nb_philo);
	e->message = sem_open("message", O_CREAT, 0600, 1);
	e->stop = sem_open("stop", O_CREAT, 0600, 1);
}

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
	if (!e.philos)
	{
		printf("[Error] Alloc' failed\n");
		exit(EXIT_FAILURE);
	}
	gettimeofday(&e.start, NULL);
	return (e);
}

t_philo	init_philo(t_env *e, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.eat = 0;
	if (e->nb_must_eat == -1)
		philo.eat = -1;
	philo.eat = 0;
	philo.dead = 0;
	philo.env = e;
	philo.last = gettime(e);
	return (philo);
}

int	philo(t_env *e, int id)
{
	t_philo philo;

	printf("Process %d\n", id);
	philo = init_philo(e, id);
	if (pthread_create(&e->checker, NULL, &check, &philo))
	{
		printf("[Error] Thread failed\n");
	}
	print(&philo, "is thinking\n");
	usleep(id % 2 * e->time_to_eat / 4 * 1000);
	while (!philo.dead && philo.eat != philo.env->nb_must_eat)
	{
		eat(e, &philo);
		sleeping(e, &philo);
		print(&philo, "is thinking\n");
	}
	pthread_join(e->checker, NULL);
	if (philo.dead)
		return (0);
	return (1);
}

void	waitall(t_env *e)
{
	int i;
	int	status;

	i = 0;
	while (i < e->nb_philo)
	{
		waitpid(e->philos[i], &status, 0);
		printf("STATUS : %d", status);
		i++;
	}
	sem_post(e->stop);
}

int	create_process(t_env *e)
{
	int	pid;
	int	i;

	i = 0;
	while (i < e->nb_philo)
	{
		pid = fork();
		if (!pid)
		{
			philo(e, i);
		}
		e->philos[i] = pid;
		i++;
	}
	return (pid);
}

void	kill_everyone(t_env *e)
{
	int	i;

	i = 0;
	while (i < e->nb_philo)
	{
		kill(e->philos[i], 2);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_env	e;
	int		pid;
	int		ret;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid Arguments\n");
		return (1);
	}
	e = init_env(argc, argv);
	printf("MUST EAT %d\n", e.nb_must_eat);
	init_sem(&e);
	sem_wait(e.stop);
	pid = create_process(&e);
	if (pid)
	{
		waitall(&e);
		sem_wait(e.stop);
		kill_everyone(&e);
	}
	free(e.philos);
	sem_close(e.fork);
	sem_close(e.stop);
	sem_close(e.message);
	return (0);
}
