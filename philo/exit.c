/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:14 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/07 17:48:10 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	freefork(t_data *d)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&d->tab_philo[i].l_fork->mutex);
	free(d->tab_philo[i].l_fork);
	while (i < d->env.nb_philo && d->env.nb_philo != 1)
	{
		pthread_mutex_destroy(&d->tab_philo[i].r_fork->mutex);
		free(d->tab_philo[i].r_fork);
		i++;
	}
}

void	freeall(t_data *d)
{
	freefork(d);
	free(d->tab_philo);
}

void	error(t_data *d)
{
	if (d->tab_philo)
		free(d->tab_philo);
	printf("Error\n");
	exit(EXIT_FAILURE);
}


