/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:18:40 by atamas            #+#    #+#             */
/*   Updated: 2024/09/28 03:22:37 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	print_message(t_philo *philo, char *message)
{
	size_t	time;

	time = (get_time() - philo->table->start);
	pthread_mutex_lock(&philo->table->deadmutex);
	pthread_mutex_lock(&philo->table->mealmutex);
	if (!philo->table->dead && philo->table->full == 0)
		printf("%zu %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->table->mealmutex);
	pthread_mutex_unlock(&philo->table->deadmutex);
}

int	philo_sleep(t_philo *philo)
{
	if (dead_or_full(philo))
		return (1);
	print_message(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
	return (0);
}

void	*routine(void *prog)
{
	t_philo	*philo;

	philo = prog;
	pthread_mutex_lock(&philo->table->mealmutex);
	philo->last_meal = get_time() + philo->table->time_to_die;
	pthread_mutex_unlock(&philo->table->mealmutex);
	while (1)
	{
		if (eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
		if (dead_or_full(philo))
			break ;
	}
	return (NULL);
}

void	case_one(t_table *table)
{
	table->start = get_time();
	printf("%zd %d has taken a fork\n", get_time() - table->start, 1);
	ft_usleep(table->time_to_die);
	printf("%zd %d died\n", get_time() - table->start, 1);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	if (!input_valid(argc, argv, &table))
		return (1);
	if (init_forks_and_philos(&table))
		return (1);
	if (table.nmbr_of_philos == 1)
		return (case_one(&table), 0);
	table.start = get_time();
	i = 0;
	while (i < table.nmbr_of_philos)
	{
		if (pthread_create(&table.philos[i].thread, NULL,
				&routine, &table.philos[i]) == 1)
			return (printf("Error\n"), 1);
		i++;
	}
	monitor(&table);
	clean_exit(&table);
}
