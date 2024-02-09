/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:52:13 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/09 18:12:15 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	init_data(int argc, char *argv[])
{
	t_data	data;

	data.env = malloc(sizeof(t_env));
	if (!data.env)
		error(&data);
	data.env->nb_philo = ft_atoi(argv[1]);
	data.env->time_to_die = ft_atoi(argv[2]);
	data.env->time_to_eat = ft_atoi(argv[3]);
	data.env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.env->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		data.env->number_of_times_each_philo_must_eat = -1;
	data.tab_philo = malloc(sizeof(t_philo) * data.env->nb_philo);
	if (!data.tab_philo)
		error(&data);
	if (pthread_mutex_init(&data.env->print_mutex, NULL))
		exit(EXIT_FAILURE);
	gettimeofday(&data.env->start, NULL);
	return (data);
}

void	is_dead(t_philo *philo)
{
	struct	timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (philo->status && current_time.tv_usec >= philo->last.tv_usec + (philo->env->time_to_die * 1000))
	{
		print_action(philo, 4);
		philo->status = 0;
	}
}

void	*nothing(void *data)
{
	t_philo	*philo;
	int		pass;

	philo = (t_philo *) data;
	pass = 0;
	// printf("Thread %d create\n", philo->id);
	while (philo->status)
	{
		if (philo->count_eat == philo->env->number_of_times_each_philo_must_eat)
			philo->status = 0;
		print_action(philo, 0);
		if (!pass && philo->id % 2 == 1)
		{
			usleep(philo->env->time_to_eat);
			pass = 1;
		}
		eat(philo);
		sleeping(philo);
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
	while (i < d->env->nb_philo)
	{
		d->tab_philo[i].id = i;
		d->tab_philo[i].status = 1;
		d->tab_philo[i].l_fork = last_fork;
		d->tab_philo[i].env = d->env;
		d->tab_philo[i].count_eat = 0;
		if (d->env->nb_philo != 1)
		{
			if (i == d->env->nb_philo - 1)
				d->tab_philo[i].r_fork = d->tab_philo[0].l_fork;
			else
				d->tab_philo[i].r_fork = init_fork();
			last_fork = d->tab_philo[i].r_fork;
		}
		gettimeofday(&d->tab_philo[i].last, NULL);
		i++;
	}
	i = 0;
	while (i < d->env->nb_philo)
	{
		if (pthread_create(&d->tab_philo[i].thread, NULL, &nothing, (void *)&d->tab_philo[i]))
			error(d);
		// pthread_detach(d->tab_philo[i].thread);
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
	// printf("yo\n");
	d = init_data(argc, argv);
	launch_thread(&d);
	i = 0;
	while (i < d.env->nb_philo)
	{
		usleep(d.env->time_to_die);
		pthread_join(d.tab_philo[i].thread, NULL);
		i++;
	}
	freeall(&d);
	return (1);
}
