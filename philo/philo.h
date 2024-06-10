/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atamas <atamas@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:34:15 by atamas            #+#    #+#             */
/*   Updated: 2024/06/10 17:19:26 by atamas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>

typedef struct s_table
{
	int	nmbr_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	rounds;
}	t_table;

#endif