/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:18:40 by atamas            #+#    #+#             */
/*   Updated: 2024/07/02 21:44:24 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	if (get_time() - philo->last_meal > philo->table->time_to_die)
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

int	take_right_fork(t_philo *philo)
{
	if (philo->table->dead == 1 || is_dead(philo))
		return (1);
	pthread_mutex_lock(philo->rfork);
	pthread_mutex_lock(&philo->table->print);
	printf("%zd %d has taken a fork\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

int	take_left_fork(t_philo *philo)
{
	if (philo->table->dead == 1 || is_dead(philo))
		return (1);
	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(&philo->table->print);
	printf("%zd %d has taken a fork\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

int	eat(t_philo *philo)
{
	if (philo->table->dead == 1 || is_dead(philo))
		return (1);
	if (philo->id % 2 == 1)
	{
		if (take_right_fork(philo) == 1)
			return (1);
		if (take_left_fork(philo) == 1)
			return (pthread_mutex_unlock(philo->rfork), 1);
	}
	else
	{
		if (take_left_fork(philo) == 1)
			return (1);
		if (take_right_fork(philo) == 1)
			return (pthread_mutex_unlock(philo->lfork), 1);
	}
	pthread_mutex_lock(&philo->table->print);
	printf("%zd %d is eating\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	philo->last_meal = get_time() + philo->table->time_to_eat;
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (philo->table->dead == 1)
		return (1);
	pthread_mutex_lock(&philo->table->print);
	printf("%zd %d is sleeping\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	ft_usleep(philo->table->time_to_sleep);
	return (0);
}

int	think(t_philo *philo)
{
	if (philo->table->dead == 1 || is_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->table->print);
	printf("%zd %d is thinking\n", get_time() - philo->table->start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

void	*routine(void *prog)
{
	t_philo	*philo;

	philo = prog;
	while (1)
	{
		if (eat(philo) == 1)
			break ;
		if (philo_sleep(philo) == 1)
			break ;
		if (think(philo) == 1)
			break ;
	}
	printf("Routine ended\n");
	return (NULL);
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
}
