#include "philo.h"

int	create_data(t_philo_data *data)
{
	data->philo = malloc(data->num_of_philo
			* (sizeof(pthread_t) + sizeof(t_state)
				+ sizeof(pthread_mutex_t) + sizeof(t_ulong)));
	if (!data->philo)
		return (-1);
	return (0);
}
