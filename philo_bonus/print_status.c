#include <stdio.h>
#include "philo_time.h"
#include "philo_types.h"

int	print_status(t_philo *philo, enum e_state status)
{
	if (pthread_mutex_lock(&philo->table->print))
		return (-1);
	printf("%lu\t%d ", philo_timer(CURR) / 1000, philo->seat);
	if (status == FORK)
		printf("has taken a fork\n");
	else if (status == EATING)
		printf("is eating\t\t%d\n", philo->ct_of_eat);
	else if (status == SLEEPING)
		printf("is sleeping\n");
	else if (status == THINKING)
		printf("is thinking\n");
	else if (status == DEAD)
		printf("is dead\n");
	if (pthread_mutex_unlock(&philo->table->print))
		return (-1);
	return (0);
}

int	put_error(char *errmsg)
{
	printf("%s\n", errmsg);
	return (-1);
}
