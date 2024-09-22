/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:34:15 by atamas            #+#    #+#             */
/*   Updated: 2024/09/23 00:41:27 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	unsigned int	meals;
	unsigned long int		last_meal;
	int	*rfork;
	int	*lfork;
	t_table			*table;
}	t_philo;

typedef struct s_table
{
	int				nmbr_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				rounds;
	size_t			start;
	int				forks[200];
	pthread_mutex_t	fork_state;
	t_philo			philos[200];
	pthread_mutex_t	deadmutex;
	int				dead;
	pthread_mutex_t	print;
}	t_table;

int		input_valid(int argc, char **argv, t_table *table);
int		ft_atol(char *string, int *error);
void	fill_values(int argc, char **argv, t_table *table, int *error);
void	destroy_forks(t_table *table);
int		init_forks_and_philos(t_table *table);
void	ft_usleep(size_t mseconds);
size_t	get_time(void);
int	take_forks(t_philo *philo);

#endif