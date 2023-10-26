#ifndef PHILO_TYPES_H
# define PHILO_TYPES_H

# include <pthread.h>
# include "typeft.h"

enum e_opr
{
	START,
	CURR
};

typedef unsigned long int	t_time_nanosec;

enum e_state
{
	FORK,
	EATING,
	THINKING,
	SLEEPING,
	DEAD
};

typedef struct s_philo
{
	t_uint					seat;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	struct s_table			*table;
	_Atomic(t_time_nanosec)	last_eat;
	int						ct_of_eat;
}	t_philo;

typedef struct s_table
{
	t_uint					num_of_philo;
	t_ulong					time_to_die;
	t_ulong					time_to_eat;
	t_ulong					time_to_sleep;
	int						min_ct_of_eat;
	_Atomic(int)			flag_death;
	_Atomic(int)			flag_done;
	pthread_mutex_t			monitor;
	pthread_mutex_t			print;
	t_philo					*philo;
	pthread_mutex_t			*fork;
	_Atomic(t_time_nanosec)	start;
	_Atomic(t_time_nanosec (*)(enum e_opr))	timer;
}	t_table;
#endif
