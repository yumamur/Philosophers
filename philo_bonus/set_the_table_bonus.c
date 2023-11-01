/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_the_table_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumamur <yumamur@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:17:48 by yumamur           #+#    #+#             */
/*   Updated: 2023/11/01 13:17:48 by yumamur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include "philo_types_bonus.h"

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

int	set_the_table(int argc, char *argv[], t_table *table)
{
	t_uint	i;

	*table = (t_table){};
	if (parse_args(argc, argv, table))
		return (-1);
	table->philos = malloc(table->num_of_philo * sizeof(*table->philos));
	memset(table->philos, 0, table->num_of_philo * sizeof(*table->philos));
	if (!table->philos)
		return (-1);
	sem_unlink("/monitor_semaphore");
	sem_unlink("/print_semaphore");
	sem_unlink("/forks_semaphore");
	table->monitor = sem_open("/monitor_semaphore", O_CREAT, 0644, 1);
	table->print = sem_open("/print_semaphore", O_CREAT, 0644, 1);
	table->forks
		= sem_open("/forks_semaphore", O_CREAT, 0644, table->num_of_philo);
	i = 0;
	while (i < table->num_of_philo)
	{
		table->philos[i] = (t_philo){};
		table->philos[i].seat = i + 1;
		table->philos[i].table = table;
		++i;
	}
	return (0);
}
