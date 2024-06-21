/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:34:15 by atamas            #+#    #+#             */
/*   Updated: 2024/06/21 16:31:25 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id; // have to start from 1 //
	pthread_t		thread;
	long int		last_meal;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
}	t_philo;

typedef struct s_table
{
	int				nmbr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				rounds;
	pthread_mutex_t	forks[200];
	t_philo			philos[200];
	int				death; //mutex
	int				print; //mutex
}	t_table;

#endif