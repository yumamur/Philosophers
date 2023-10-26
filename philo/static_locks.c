#include "philo_mutex.h"

static int inline
	static_lock_inline(pthread_mutex_t *mutex, enum e_opr_mutex opr)
{
	if (opr == INIT)
		return (pthread_mutex_init(mutex, NULL));
	else if (opr == DESTROY)
		return (pthread_mutex_destroy(mutex));
	else if (opr == LOCK)
		return (pthread_mutex_lock(mutex));
	else if (opr == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	else
		return (-1);
}

int	print_mutex(enum e_opr_mutex opr)
{
	static pthread_mutex_t	mutex;

	return (static_lock_inline(&mutex, opr));
}

int	monitor_mutex(enum e_opr_mutex opr)
{
	static pthread_mutex_t	mutex;

	return (static_lock_inline(&mutex, opr));
}
