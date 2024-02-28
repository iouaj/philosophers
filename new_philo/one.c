/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:30:02 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/28 18:44:14 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *one(void *arg)
{

}

static void	launch_thread(t_env *env)
{

	env->philos[0].id = 0;
	env->philos[0].env = env;
	env->philos[0].l_fork = init_fork();
	env->philos[0].r_fork
	env->philos[0].eat = 0;
	if (pthread_create(&env->philos[0].thread, NULL, &one, (void *)&(env->philos[0])))
		exit(EXIT_FAILURE);
}

int	main_one(t_env env)
{

}
