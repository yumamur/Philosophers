#ifndef PHILO_DATATYPES_H
# define PHILO_DATATYPES_H

# include <sys/time.h>
# include <pthread.h>
# include "typeft.h"

typedef enum e_state
{
	ON_HOLD,
	EATING,
	THINKING,
	SLEEPING,
	DEAD
}	t_state;

typedef struct s_data
{
	t_uint			num_of_philo;
	t_uint			time_to_die;
	t_uint			time_to_eat;
	t_uint			time_to_sleep;
	t_uint			min_ct_of_eat;
	pthread_t		*philo;
	t_state			*state;
	pthread_mutex_t	*fork;
	t_ulong			*last_eat;
	t_uint			*ct_of_eat;
	struct timeval	time_start;
	pthread_mutex_t	death;
}	t_philo_data;
#endif
