#ifndef PHILO_ERRNO_H
# define PHILO_ERRNO_H

# ifndef PHILO_TEST
#  define PERR_TIMER	""
#  define PERR_TCRT		""
#  define PERR_TDTR		""
#  define PERR_TJOIN	""
#  define PERR_TDETACH	""
#  define PERR_MLOCK	""
#  define PERR_MUNLOCK	""
# else
#  define PERR_TIMER		"gettimeofday failure"
#  define PERR_TCRT		"pthread_create failure"
#  define PERR_TDTR		"pthread_mutex_destroy failure"
#  define PERR_TJOIN		"pthread_join failure"
#  define PERR_TDETACH	"pthread_detach failure"
#  define PERR_MLOCK		"pthread_mutex_lock failure"
#  define PERR_MUNLOCK	"pthread_mutex_unlock failure"

# endif /* PHILO_TEST */

int		put_error(const char *errmsg __attribute__((unused)));
#endif