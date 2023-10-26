#ifndef PHILO_MUTEX_H
# define PHILO_MUTEX_H

# include <pthread.h>
# include "philo_types.h"

int	print_mutex(enum e_opr_mutex opr);
int	monitor_mutex(enum e_opr_mutex opr);
#endif
