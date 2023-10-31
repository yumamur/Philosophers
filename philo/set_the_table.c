#include <limits.h>
#include <string.h>
#include <pthread.h>
#include "philo_types.h"

static int	atoui_v2(t_c_char *str, t_uint *ptr)
{
	t_ulong	ret;
	t_uint	i;

	if (!str || !*str)
		return (-1);
	i = 0;
	ret = 0;
	while (str[i] >= '0' && str[i] <= '9' && i < 10)
	{
		ret = (str[i] - 48) + (ret * 10);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	if (ret > INT_MAX)
		return (-1);
	*ptr = ret;
	return (0);
}

static int	parse_args(int argc, char **argv, t_table *table)
{
	int	err;

	err = 0;
	err += atoui_v2(argv[2], &table->num_of_philo);
	table->time_to_die = (t_ulong)table->num_of_philo;
	err += atoui_v2(argv[3], &table->num_of_philo);
	table->time_to_eat = (t_ulong)table->num_of_philo;
	err += atoui_v2(argv[4], &table->num_of_philo);
	table->time_to_sleep = (t_ulong)table->num_of_philo;
	if (argc == 6)
	{
		err += atoui_v2(argv[5], &table->num_of_philo);
		table->min_num_of_eat = table->num_of_philo;
	}
	else
		table->min_num_of_eat = -1;
	err += atoui_v2(argv[1], &table->num_of_philo);
	if (err)
		return (-1);
	return (0);
}

static int	init_table(int argc, char *argv[], t_table *table)
{
	*table = (t_table){};
	if (parse_args(argc, argv, table))
		return (-1);
	table->philos = malloc(table->num_of_philo
			* (sizeof(*table->philos) + sizeof(*table->forks)));
	memset(table->philos, 0, table->num_of_philo * (sizeof(*table->philos)
			+ sizeof(*table->forks)));
	if (!table->philos)
		return (-1);
	table->forks = (void *)(table->philos + table->num_of_philo);
	return (0);
}

int	set_the_table(int argc, char *argv[], t_table *table)
{
	t_uint	i;

	if (init_table(argc, argv, table))
		return (-1);
	pthread_mutex_init(&table->monitor, NULL);
	pthread_mutex_init(&table->print, NULL);
	i = 0;
	while (i < table->num_of_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (-1);
		table->philos[i] = (t_philo){};
		table->philos[i].seat = i + 1;
		table->philos[i].table = table;
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork
			= &table->forks[(i + 1) % table->num_of_philo];
		++i;
	}
	return (0);
}
