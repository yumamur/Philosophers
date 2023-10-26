#include "philo.h"
#include <string.h>
#include <limits.h>

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
	table->time_to_die = (t_ulong)table->num_of_philo * 1000L;
	err += atoui_v2(argv[3], &table->num_of_philo);
	table->time_to_eat = (t_ulong)table->num_of_philo * 1000L;
	err += atoui_v2(argv[4], &table->num_of_philo);
	table->time_to_sleep = (t_ulong)table->num_of_philo * 1000L;
	if (argc == 6)
	{
		err += atoui_v2(argv[5], &table->num_of_philo);
		table->min_ct_of_eat = table->num_of_philo;
	}
	else
		table->min_ct_of_eat = -1;
	err += atoui_v2(argv[1], &table->num_of_philo);
	if (err)
		return (-1);
	return (0);
}

int	init_table(int argc, char *argv[], t_table *table)
{
	*table = (t_table){};
	table->timer = philo_timer;
	if (parse_args(argc, argv, table))
		return (-1);
	table->philo = malloc(table->num_of_philo
			* (sizeof(*table->philo) + sizeof(*table->fork)));
	memset(table->philo, 0, table->num_of_philo * (sizeof(*table->philo)
			+ sizeof(*table->fork)));
	if (!table->philo)
		return (-1);
	table->fork = (void *)(table->philo + table->num_of_philo);
	return (0);
}
