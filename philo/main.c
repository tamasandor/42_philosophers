/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:18:40 by atamas            #+#    #+#             */
/*   Updated: 2024/06/24 20:26:07 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_table *table)
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
	i = 1;
	while (i < table->nmbr_of_philos)
	{
		table->philos[i].lfork = &table->forks[i];
		table->philos[i].rfork = &table->forks[i - 1];
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

int	main(int argc, char **argv)
{
	t_table	table;

	if (!input_valid(argc, argv, &table))
		return (1);
	if (init_forks(&table))
		return (1);
}
