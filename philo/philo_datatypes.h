#ifndef PHILO_DATATYPES_H
# define PHILO_DATATYPES_H

# include "typeft.h"

typedef struct s_data
{
	t_uint	num_of_philo;
	t_uint	time_to_die;
	t_uint	time_to_eat;
	t_uint	time_to_sleep;
	t_uint	min_ct_of_eat;
}	t_data;
#endif
