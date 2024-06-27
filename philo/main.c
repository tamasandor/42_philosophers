/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:18:40 by atamas            #+#    #+#             */
/*   Updated: 2024/06/27 15:45:53 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks_and_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nmbr_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (printf("Error initializing mutex for forks\n"), 1);
		i++;
	}
	table->philos[0].lfork = &table->forks[0];
	table->philos[0].rfork = &table->forks[table->nmbr_of_philos - 1];
	table->philos[0].id = 1;
	table->philos[0].table = table;
	i = 1;
	while (i < table->nmbr_of_philos)
	{
		table->philos[i].lfork = &table->forks[i];
		table->philos[i].rfork = &table->forks[i - 1];
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		i++;
	}
	return (0);
}

void	destroy_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nmbr_of_philos)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}



int	is_dead(t_philo *philo)
{
	if (philo->last_meal + get_time() > philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->deadmutex);
		pthread_mutex_lock(&philo->table->print);
		philo->table->dead = 1;
		printf("%zd %d died\n", philo->table->start - get_time(), philo->id);
		pthread_mutex_unlock(&philo->table->deadmutex);
		pthread_mutex_unlock(&philo->table->print);
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%zd %d is sleeping\n", philo->table->start - get_time(), philo->id);
	pthread_mutex_unlock(&philo->table->print);
	ft_usleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%zd %d is thinking\n", philo->table->start - get_time(), philo->id);
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
