#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include "philo_types.h"

t_time	nanotime(void);
int		p_sleep(t_flag *death, t_time length);

#endif
