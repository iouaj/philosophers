/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:52:13 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/07 18:06:26 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(int argc, char *argv[])
{
	t_data	data;

	data.env.nb_philo = ft_atoi(argv[1]);
	data.env.time_to_die = ft_atoi(argv[2]);
	data.env.time_to_eat = ft_atoi(argv[3]);
	data.env.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.env.number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	data.tab_philo = malloc(sizeof(t_philo) * data.env.nb_philo);
	if (!data.tab_philo)
		error(&data);
	gettimeofday(&data.env.start, NULL);
	return (data);
}

void	is_dead(t_philo *philo)
{
	struct	timeval	current_time;

	printf("check\n");
	gettimeofday(&current_time, NULL);
	if (current_time.tv_usec >= philo->last.tv_usec + philo->env.time_to_die)
	{
		printf("check\n");
		philo->status = 0;
		printf("%ldsec Philosopher %d died\n", gettime(philo), philo->id);
	}
}

void	*nothing(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	printf("%d\n", philo->id);
	printf("%ld\n", philo->last.tv_usec);
	printf("mini check\n");
	printf("%d\n", philo->env.time_to_die);
	while (philo->status)
	{
		is_dead(philo);
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

void	launch_thread(t_data *d)
{
	int	i;
	t_fork *last_fork;

	i = 0;
	last_fork = init_fork();
	while (i < d->env.nb_philo)
	{
		d->tab_philo[i].id = i;
		d->tab_philo[i].status = 1;
		d->tab_philo[i].l_fork = last_fork;
		if (d->env.nb_philo != 1)
		{
			d->tab_philo[i].r_fork = init_fork();
			last_fork = d->tab_philo[i].r_fork;
		}
		gettimeofday(&d->tab_philo[i].last, NULL);
		if (pthread_create(&d->tab_philo[i].thread, NULL, nothing, (void *)(&d->tab_philo[i])))
			error(d);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	d;
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid Format\n");
		return (1);
	}
	printf("yo\n");
	d = init_data(argc, argv);
	launch_thread(&d);
	i = 0;
	while (i < d.env.nb_philo)
	{
		pthread_join(d.tab_philo[i].thread, NULL);
		usleep(100);
		i++;
	}
	freeall(&d);
	return (1);
}
