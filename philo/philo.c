/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:52:13 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/06 17:59:17 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	freetabphilo(t_data *d)
{
	// int	i;

	// i = 0;
	// while (i < d->nb_philo && d->tab_philo[i])
	// {
	// 	free(d->tab_philo[i]);
	// 	i++;
	// }
	free(d->tab_philo);
}

void	error(t_data *d)
{
	if (d->tab_philo)
		freetabphilo(d);
	printf("Error\n");
	exit(EXIT_FAILURE);
}

t_data	init_data(int argc, char *argv[])
{
	t_data	data;

	data.nb_philo = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	data.tab_philo = malloc(sizeof(pthread_t) * data.nb_philo);
	if (!data.tab_philo)
		error(&data);
	return (data);
}

void	*nothing(void *ptr)
{
	printf("Bip Boop\n");
	return (ptr);
}

void	launch_thread(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nb_philo)
	{
		printf("try thread\n");
		if (pthread_create(&d->tab_philo[i], NULL, nothing, NULL))
			error(d);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	d;

	printf("yo\n");
	if (argc != 5 && argc != 6)
	{
		printf("Invalid Format\n");
		return (1);
	}
	d = init_data(argc, argv);
	launch_thread(&d);
	pthread_join(d.tab_philo[0], NULL);
	freetabphilo(&d);
	return (1);
}
