#include "philo.h"

int	create_data(t_philo_data *data)
{
	data->philo = malloc(data->num_of_philo
			* (sizeof(*data->philo) + sizeof(*data->state)
				+ sizeof(*data->fork) + sizeof(*data->last_eat)
				+ sizeof(*data->ct_of_eat)));
	if (!data->philo)
		return (-1);
	data->state = (void *)(data->philo + data->num_of_philo);
	data->fork = (void *)(data->state + data->num_of_philo);
	data->last_eat = (void *)(data->fork + data->num_of_philo);
	data->ct_of_eat = (void *)(data->last_eat + data->num_of_philo);
	return (0);
}
