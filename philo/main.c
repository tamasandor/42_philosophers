/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:18:40 by atamas            #+#    #+#             */
/*   Updated: 2024/09/23 12:39:04 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->deadmutex);
	if (philo->table->dead == 1)
	return (pthread_mutex_unlock(&philo->table->deadmutex), 1);
	if ((get_time() - philo->last_meal) >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->print);
		philo->table->dead = 1;
		printf("%zd %d died\n", get_time() - philo->table->start, philo->id);
		pthread_mutex_unlock(&philo->table->print);
		return (pthread_mutex_unlock(&philo->table->deadmutex), 1);
	}
	pthread_mutex_unlock(&philo->table->deadmutex);
	return (0);
}

int	take_right_fork(t_philo *philo)
{
	int	success;

	success = 0;
	if (is_dead(philo))
		return (1);
	while (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->table->fork_state);
		if (*philo->rfork == 0)
		{
			*philo->rfork = 1;
			pthread_mutex_lock(&philo->table->print);
			if (philo->table->dead != 1)
				printf("%zd %d has taken a fork\n", get_time() - philo->table->start, philo->id);
			pthread_mutex_unlock(&philo->table->print);
			pthread_mutex_unlock(&philo->table->fork_state);
			success = 1;
			break;
		}
		pthread_mutex_unlock(&philo->table->fork_state);
		ft_usleep(2);
	}
	return (success);
}

int	take_left_fork(t_philo *philo)
{
	int	success;

	success = 0;
	if (is_dead(philo))
		return (1);
	while (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->table->fork_state);
		if (*philo->lfork == 0)
		{
			*philo->lfork = 1;
			pthread_mutex_lock(&philo->table->print);
			if (philo->table->dead != 1)
				printf("%zd %d has taken a fork\n", get_time() - philo->table->start, philo->id);
			pthread_mutex_unlock(&philo->table->print);
			pthread_mutex_unlock(&philo->table->fork_state);
			success = 1;
			break;
		}
		pthread_mutex_unlock(&philo->table->fork_state);
		ft_usleep(2);
	}
	return (success);
}

int	think(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->dead != 1)
		printf("%zd %d is thinking\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		if (take_left_fork(philo) == 1 && take_right_fork(philo) == 1)
		{
			return (1);
		}
	}
	else
	{
		if (take_right_fork(philo) == 1 && take_left_fork(philo) == 1)
		{
			return (1);
		}
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (is_dead(philo))
		return (0);
	if (philo->id % 2 == 1 && philo->meals == 0)
	{
		think(philo);
		ft_usleep(philo->table->time_to_eat / 2);
	}
	if (take_forks(philo) == 0)
		return (is_dead(philo));
	if (is_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->table->print);
	printf("%zd %d is eating\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	printf("DEBUG: %lu\n", philo->last_meal);
	philo->last_meal = (get_time() - philo->table->start) + philo->table->time_to_eat;
	printf("DEBUG: %lu\n", philo->last_meal);
	philo->meals += 1;
	pthread_mutex_lock(&philo->table->fork_state);
	*philo->lfork = 0;
	*philo->rfork = 0;
	pthread_mutex_unlock(&philo->table->fork_state);
	ft_usleep(philo->table->time_to_eat);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->dead != 1)
		printf("%zd %d is sleeping\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	ft_usleep(philo->table->time_to_sleep);
	return (0);
}

void	*routine(void *prog)
{
	t_philo	*philo;

	philo = prog;
	philo->last_meal = philo->table->start;
	printf("DEBUG: %lu\n", philo->last_meal);
	while (1)
	{
		if (is_dead(philo))
			break ;
		if (eat(philo) == 1)
			break ;
		if (philo_sleep(philo) == 1)
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
	int		j;

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
		if (pthread_create(&table.philos[i].thread, NULL, &routine, &table.philos[i]) == 1)
			return (printf("Error\n"), 1);
		i++;
	}
	j = 0;
	while (j < table.nmbr_of_philos)
	{
		pthread_join(table.philos[j].thread, NULL);
		j++;
	}
	destroy_forks(&table);
}
