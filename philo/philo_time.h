#ifndef PHILO_TIME_H
# define PHILO_TIME_H

# include <bits/types/struct_timeval.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
# include "philo_types.h"

t_time_nanosec	philo_timer(void);
void			precise_sleep(t_table *table, t_uint nanoseconds);

#endif
