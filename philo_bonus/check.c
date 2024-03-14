/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:12:42 by iouajjou          #+#    #+#             */
/*   Updated: 2024/03/13 19:26:41 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *check(void *arg)
{
	t_philo				*philo;
	long unsigned int	to_die;

	philo = (t_philo *) arg;
	to_die = philo->env->time_to_die;
	while (1)
	{
		// printf("%d Check\n", philo->id);
		if (gettime(philo->env) - philo->last >= to_die)
		{
			print(philo, "is dead\n");
			philo->dead = 1;
			sem_post(philo->env->stop);
			break ;
		}
		if (philo->eat == philo->env->nb_must_eat)
			break ;
	}
	return (NULL);
}

// static int	dead(t_env *e)
// {
// 	int					i;
// 	int					count;
// 	long unsigned int	to_die;

// 	i = 0;
// 	count = 0;
// 	to_die = (long unsigned int)e->time_to_die;
// 	while (i < e->nb_philo)
// 	{
// 		if (e->philos[i].eat != e->nb_must_eat)
// 		{
// 			if (gettime(e) - e->philos[i].last >= to_die)
// 			{
// 				e->dead = 1;
// 				printf("%ld %d is dead\n", gettime(e), i);
// 				return (-1);
// 			}
// 		}
// 		else
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

// int	is_philo_dead(t_env *env)
// {
// 	int	count;

// 	if (env->dead)
// 		return (1);
// 	count = dead(env);
// 	if (count == env->nb_philo)
// 		return (2);
// 	if (count == -1)
// 		return (1);
// 	return (0);
// }
