#include "philo_time.h"
#include "typeft.h"
#include <unistd.h>

t_time_nanosec	philo_timer(enum e_opr opr)
{
	static struct timeval	start;

	if (opr == START)
		return (gettimeofday((struct timeval *)&start, NULL));
	else
	{
		typeof(start) tmp;
		gettimeofday(&tmp, NULL);
		return ((tmp.tv_sec - start.tv_sec) * 1000000L
			+ tmp.tv_usec - start.tv_usec);
	}
}

int	precise_sleep(t_uint nanoseconds)
{
	if (nanoseconds < 1000)
		usleep(nanoseconds);
	else
	{
		while (nanoseconds)
		{
			usleep(1000);
			nanoseconds -= 1000;
		}
	}
	return (0);
}
