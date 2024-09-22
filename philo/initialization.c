/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:25:10 by atamas            #+#    #+#             */
/*   Updated: 2024/09/22 20:49:18 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "philo.h"

int	ft_atol(char *string, int *error)
{
	long int	number;

	number = 0;
	if (*string == '+')
		string++;
	while (*string && *error == 0)
	{
		if (!(*string - '0' >= 0 && *string - '0' <= 9))
			*error = 1;
		number = number * 10 + (*string - '0');
		string++;
		if (number > INT_MAX)
			*error = 1;
	}
	if (*error == 1)
		return (0);
	return (number);
}

void	fill_values(int argc, char **argv, t_table *table, int *error)
{
	if (argc == 6)
		table->rounds = ft_atol(argv[5], error);
	table->nmbr_of_philos = ft_atol(argv[1], error);
	table->time_to_die = ft_atol(argv[2], error);
	table->time_to_eat = ft_atol(argv[3], error);
	table->time_to_sleep = ft_atol(argv[4], error);
	table->dead = 0;
}

int	input_valid(int argc, char **argv, t_table *table)
{
	int	error;

	error = 0;
	if (argc != 5 && argc != 6)
	{
		write(2, "Incorrect amount of arguments\n", 30);
		printf("Correct use is %s number_of_philos time_to_die time_to_eat "
			"time_to_sleep [round_nums]\n", argv[0]);
		return (0);
	}
	table->rounds = -1;
	fill_values(argc, argv, table, &error);
	if (table->nmbr_of_philos > 200)
	{
		write(2, "Number of philosophers must be less than 200\n", 45);
		return (0);
	}
	if (error == 1 || table->nmbr_of_philos == 0 || table->time_to_die == 0
		|| table->time_to_eat == 0 || table->time_to_sleep == 0)
	{
		write(2, "Format of the arguments are not correct\n", 40);
		return (0);
	}
	return (1);
}

void	destroy_forks(t_table *table)
{
	pthread_mutex_destroy(&table->fork_state);
	pthread_mutex_destroy(&table->deadmutex);
	pthread_mutex_destroy(&table->print);
}

int	init_forks_and_philos(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->fork_state, NULL) != 0)
		return (printf("Error initializing mutex for forks\n"), 1);
	if (pthread_mutex_init(&table->deadmutex, NULL) != 0)
		return (printf("Error initializing deadmutex\n"), 1);
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (printf("Error initializing print mutex\n"), 1);
	while (i < table->nmbr_of_philos)
	{
		table->forks[i] = 0;
		i++;
	}
	i = 0;
	while (i < table->nmbr_of_philos)
	{
		if (i == 0)
			table->philos[i].rfork = &table->forks[table->nmbr_of_philos - 1];
		else
			table->philos[i].rfork = &table->forks[i - 1];
		table->philos[i].lfork = &table->forks[i];
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		i++;
	}
	return (0);
}
