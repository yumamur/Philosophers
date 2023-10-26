#ifndef PHILO_TIME_H
# define PHILO_TIME_H

# include <bits/types/struct_timeval.h>
# include <sys/time.h>
# include <time.h>
# include "philo_types.h"

t_time_nanosec	philo_timer(enum e_opr opr);
int				precise_sleep(t_uint nanoseconds);

#endif
