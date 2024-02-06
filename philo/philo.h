/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iouajjou <iouajjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:52:27 by iouajjou          #+#    #+#             */
/*   Updated: 2024/02/06 17:58:19 by iouajjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int	nb_philo;
	int	time_to_die;//in ms
	int	time_to_eat;// in ms
	int	time_to_sleep;// in ms
	int	number_of_times_each_philo_must_eat;
	pthread_t	*tab_philo;

}	t_data;

int	ft_atoi(const char *nptr);

#endif
