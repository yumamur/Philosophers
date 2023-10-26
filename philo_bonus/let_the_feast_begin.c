#include "philo.h"
#include <string.h>

int		unset_the_table(t_table *table);
void	*philo_routine(void *ptr);
int		print_status(t_philo *philo, enum e_state status);

static int inline	monitor_inline(t_table *table)
{
	t_uint	i;

	i = 0;
	while (!table->flag_death && i < table->num_of_philo)
	{
		if (pthread_mutex_lock(&table->monitor))
			return (put_error(PERR_MLOCK));
		if (philo_timer(CURR) - table->philo[i].last_eat
			> table->time_to_die)
		{
			print_status(table->philo + i, DEAD);
			table->flag_death = 1;
			pthread_mutex_unlock(&table->monitor);
			return (1);
		}
		if (pthread_mutex_unlock(&table->monitor))
			return (put_error(PERR_MUNLOCK));
		++i;
		usleep(70);
	}
	return (0);
}

void	monitor(t_table *table)
{
	t_uint	i;

	while (!table->flag_done)
	{
		if (monitor_inline(table))
			return ;
		i = 0;
		while (table->min_ct_of_eat != -1 && i < table->num_of_philo
			&& table->philo[i].ct_of_eat >= table->min_ct_of_eat)
			++i;
		if (i == table->num_of_philo)
			table->flag_done = 1;
	}
}

static int inline	feast_inline(t_table *table, t_uint i, pthread_t *list)
{
	if (pthread_create(list + i, NULL, philo_routine, table->philo + i))
	{
		free(list);
		if (unset_the_table(table))
			put_error(PERR_TDTR);
		return (put_error(PERR_TCRT));
	}
	if (pthread_mutex_lock(&table->monitor))
	{
		free(list);
		return (put_error(PERR_MLOCK));
	}
	table->philo[i].last_eat = table->start;
	if (pthread_mutex_unlock(&table->monitor))
	{
		free(list);
		return (put_error(PERR_MUNLOCK));
	}
	usleep(100);
	return (0);
}

int	let_the_feast_begin(t_table *table)
{
	pthread_t	*list;
	t_uint		i;

	list = malloc(table->num_of_philo * sizeof(pthread_t));
	memset(list, 0, table->num_of_philo * sizeof(pthread_t));
	if (!list)
		return (-1);
	i = 0;
	table->start = table->timer(START);
	while (i < table->num_of_philo)
	{
		if (feast_inline(table, i, list))
			return (-1);
		++i;
	}
	monitor(table);
	pthread_mutex_destroy(&table->monitor);
	pthread_mutex_destroy(&table->print);
	i = 0;
	while (i < table->num_of_philo)
	{
		pthread_mutex_destroy(&table->fork[i++]);
		pthread_join(list[i], NULL);
	}
	return (0);
}
