/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_types_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumamur <yumamur@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:16:37 by yumamur           #+#    #+#             */
/*   Updated: 2023/11/01 13:16:37 by yumamur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TYPES_BONUS_H
# define PHILO_TYPES_BONUS_H

# include <semaphore.h>
# include <signal.h>
# include "typeft_bonus.h"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "is dead"

typedef _Atomic(int)		t_flag;
typedef _Atomic(long)		t_time;

typedef struct s_philo		t_philo;
typedef struct s_table		t_table;

struct s_philo
{
	t_uint			seat;
	t_table			*table;
	t_time			last_eat;
	_Atomic(int)	ct_of_eat;
};

struct s_table
{
	t_uint	num_of_philo;
	t_uint	time_to_die;
	t_uint	time_to_eat;
	t_uint	time_to_sleep;
	int		min_num_of_eat;
	t_philo	*philos;
	sem_t	*forks;
	sem_t	*monitor;
	sem_t	*print;
	t_flag	death;
	t_flag	done;
	t_time	start;
};

#endif
