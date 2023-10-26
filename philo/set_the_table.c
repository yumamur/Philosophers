#include "philo.h"

int	unset_the_table(t_table *table)
{
	memset(table->philo, 0, table->num_of_philo
		* (sizeof(*table->philo) + sizeof(*table->fork)));
	free(table->philo);
	return (0);
}

int	set_the_table(t_table *table)
{
	t_uint	i;

	if (monitor_mutex(INIT))
		return (-1);
	if (print_mutex(INIT))
		return (-1);
	i = 0;
	while (i < table->num_of_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
			return (-1);
		table->philo[i] = (t_philo){};
		table->philo[i].seat = i + 1;
		table->philo[i].table = table;
		table->philo[i].right_fork = &table->fork[i];
		table->philo[i].left_fork = &table->fork[(i + 1) % table->num_of_philo];
		++i;
	}
	return (0);
}
