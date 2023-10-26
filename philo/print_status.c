#include <stdio.h>
#include "philo_time.h"
#include "philo_mutex.h"

#ifndef PHILO_TEST
# define DIVIDER 1000L
#else
# define DIVIDER 1L
#endif

int	print_status(t_philo *philo, enum e_state status)
{
	if (print_mutex(LOCK))
		return (-1);
	if (!philo->table->flag_death && !philo->table->flag_done)
	{
		printf("%lu\t%d ", (philo_timer() - philo->table->init) / DIVIDER,
			philo->seat);
		if (status == FORK)
			printf("has taken a fork\n");
		else if (status == EATING)
			printf("is eating\n");
		else if (status == SLEEPING)
			printf("is sleeping\n");
		else if (status == THINKING)
			printf("is thinking\n");
		else if (status == DEAD)
			printf("is dead\n");
	}
	return (print_mutex(UNLOCK));
}

#ifndef PHILO_TEST

int	put_error(const char *errmsg __attribute__((unused)))
{
	return (-1);
}

#else

int	put_error(const char *errmsg)
{
	printf("%s\n", errmsg);
	return (-1);
}
#endif
