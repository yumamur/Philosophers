#include "philo.h"
#include "typeft.h"
#include <string.h>

int	unset_the_table(t_table *table)
{
	t_uint	i;

	if (pthread_mutex_destroy(&table->monitor)
		|| pthread_mutex_destroy(&table->print))
		return (-1);
	i = 0;
	while (i < table->num_of_philo)
	{
		if (pthread_mutex_destroy(&table->fork[i++]))
			return (-1);
	}
	memset(table->philo, 0, table->num_of_philo * sizeof(*table->philo));
	free(table->philo);
	memset(table->fork, 0, table->num_of_philo * sizeof(*table->fork));
	free(table->fork);
	return (0);
}

int	set_the_table(t_table *table)
{
	t_uint	i;

	if (pthread_mutex_init(&table->monitor, NULL)
		|| pthread_mutex_init(&table->print, NULL))
		return (-1);
	i = 0;
	while (i < table->num_of_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
			return (-1);
		table->philo[i] = (t_philo){};
		table->philo[i].seat = i + 1;
		table->philo[i].table = table;
		if (i < table->num_of_philo - 1)
			table->philo[i].right_fork = &table->fork[i];
		else
			table->philo[i].right_fork = &table->fork[table->num_of_philo - 1];
		if (i < table->num_of_philo - 1)
			table->philo[i].left_fork = &table->fork[i + 1];
		else
			table->philo[i].left_fork = &table->fork[0];
		++i;
	}
	return (0);
}
