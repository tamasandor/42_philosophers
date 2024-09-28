/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 03:09:11 by atamas            #+#    #+#             */
/*   Updated: 2024/09/28 03:12:13 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_right_fork(t_philo *philo)
{
	if (dead_or_full(philo))
		return (1);
	pthread_mutex_lock(philo->rfork);
	print_message(philo, "has taken a fork");
	return (0);
}

int	take_left_fork(t_philo *philo)
{
	if (dead_or_full(philo))
		return (1);
	pthread_mutex_lock(philo->lfork);
	print_message(philo, "has taken a fork");
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 1 && philo->meals == 0)
	{
		print_message(philo, "is thinking");
		ft_usleep(philo->table->time_to_eat / 2);
	}
	if (philo->id % 2 == 0)
	{
		if (take_right_fork(philo))
			return (1);
		if (take_left_fork(philo))
			return (pthread_mutex_unlock(philo->rfork), 1);
	}
	else
	{
		if (take_left_fork(philo))
			return (1);
		if (take_right_fork(philo))
			return (pthread_mutex_unlock(philo->lfork), 1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->table->mealmutex);
	philo->meals += 1;
	philo->last_meal = get_time() + philo->table->time_to_die;
	pthread_mutex_unlock(&philo->table->mealmutex);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	return (0);
}
