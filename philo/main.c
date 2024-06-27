/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:18:40 by atamas            #+#    #+#             */
/*   Updated: 2024/06/27 16:00:50 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (philo->last_meal + get_time() > philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->deadmutex);
		pthread_mutex_lock(&philo->table->print);
		philo->table->dead = 1;
		printf("%zd %d died\n", get_time() - philo->table->start, philo->id);
		pthread_mutex_unlock(&philo->table->deadmutex);
		pthread_mutex_unlock(&philo->table->print);
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%zd %d is sleeping\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	ft_usleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%zd %d is thinking\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!input_valid(argc, argv, &table))
		return (1);
	if (init_forks_and_philos(&table))
		return (1);
}
