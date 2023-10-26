#ifndef PHILO_ERRNO_H
# define PHILO_ERRNO_H

# define PERR_TIMER		"gettimeofday failure"

# define PERR_TCRT		"pthread_create failure"
# define PERR_TDTR		"pthread_mutex_destroy failure"
# define PERR_TJOIN		"pthread_join failure"
# define PERR_TDETACH	"pthread_join failure"

# define PERR_MLOCK		"pthread_mutex_lock failure"
# define PERR_MUNLOCK	"pthread_mutex_unlock failure"

int		put_error(char *errmsg);
#endif
