#include "philo_time.h"
#include <time.h>

t_time_nanosec	philo_timer(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000L + time.tv_usec);
}

void	precise_sleep(t_table *table, t_uint nanoseconds)
{
	t_time_nanosec	cur;

	cur = philo_timer();
	while (!table->flag_death)
	{
		if (philo_timer() - cur >= nanoseconds)
		{
			break ;
		}
		usleep(1000);
	}
}
