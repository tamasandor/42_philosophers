/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:03:11 by atamas            #+#    #+#             */
/*   Updated: 2024/09/28 19:38:07 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_dead(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nmbr_of_philos)
	{
		pthread_mutex_lock(&table->mealmutex);
		if (get_time() >= table->philos[i].last_meal)
		{
			pthread_mutex_unlock(&table->mealmutex);
			print_message(&table->philos[i], "died");
			pthread_mutex_lock(&table->deadmutex);
			table->dead = 1;
			pthread_mutex_unlock(&table->deadmutex);
			return (1);
		}
		pthread_mutex_unlock(&table->mealmutex);
		i++;
	}
	return (0);
}

int	dead_or_full(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->table->deadmutex);
	pthread_mutex_lock(&philo->table->mealmutex);
	result = philo->table->dead;
	result += philo->table->full;
	pthread_mutex_unlock(&philo->table->deadmutex);
	pthread_mutex_unlock(&philo->table->mealmutex);
	return (result);
}

int	check_is_full(t_table *table)
{
	int	i;

	pthread_mutex_lock(&table->mealmutex);
	if (table->rounds == -1)
		return (pthread_mutex_unlock(&table->mealmutex), 0);
	i = 0;
	pthread_mutex_unlock(&table->mealmutex);
	while (i < table->nmbr_of_philos)
	{
		pthread_mutex_lock(&table->mealmutex);
		if (table->philos[i].meals < table->rounds)
		{
			return (pthread_mutex_unlock(&table->mealmutex), 0);
		}
		pthread_mutex_unlock(&table->mealmutex);
		i++;
	}
	pthread_mutex_lock(&table->mealmutex);
	table->full = 1;
	pthread_mutex_unlock(&table->mealmutex);
	return (1);
}

void	monitor(t_table *table)
{
	ft_usleep(50);
	while (1)
	{
		if (check_is_dead(table) || check_is_full(table))
			break ;
	}
}
