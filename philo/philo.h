/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:34:15 by atamas            #+#    #+#             */
/*   Updated: 2024/09/28 03:22:49 by atamas           ###   ########.fr       */
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
	int				meals;
	size_t			last_meal;
	int				*dead;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	t_table			*table;
	pthread_t		thread;
}	t_philo;

typedef struct s_table
{
	int				nmbr_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start;
	int				rounds;
	int				dead;
	int				full;
	pthread_mutex_t	forks[200];
	t_philo			philos[200];
	pthread_mutex_t	deadmutex;
	pthread_mutex_t	mealmutex;
	pthread_mutex_t	print;
}	t_table;

int		input_valid(int argc, char **argv, t_table *table);
int		ft_atol(char *string, int *error);
void	fill_values(int argc, char **argv, t_table *table, int *error);
void	clean_exit(t_table *table);
int		init_forks_and_philos(t_table *table);
void	ft_usleep(size_t mseconds);
size_t	get_time(void);
int		take_forks(t_philo *philo);
int		dead_or_full(t_philo *philo);
void	monitor(t_table *table);
void	print_message(t_philo *philo, char *message);
int		eat(t_philo *philo);

#endif