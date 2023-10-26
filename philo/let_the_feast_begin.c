#include "philo.h"

#ifndef PHILO_TEST
# define DIVIDER 1000L
#else
# define DIVIDER 1L
#endif

int		unset_the_table(t_table *table);
void	*philo_routine(void *ptr);
int		print_status(t_philo *philo, enum e_state status);

void	monitor(t_table *table)
{
	t_uint	i;

	while (!table->flag_done)
	{
		i = -1;
		while (!table->flag_death && ++i < table->num_of_philo)
		{
			monitor_mutex(LOCK);
			if (philo_timer() - table->philo[i].last_eat > table->time_to_die)
			{
				print_status(table->philo + i, DEAD);
				table->flag_death = 1;
			}
			monitor_mutex(UNLOCK);
			usleep(100);
		}
		if (table->flag_death)
			break ;
		i = 0;
		while (table->min_ct_of_eat != -1 && i < table->num_of_philo
			&& table->philo[i].ct_of_eat >= table->min_ct_of_eat)
			i++;
		if (i == table->num_of_philo)
			table->flag_done = 1;
	}
}


int	let_the_feast_begin(t_table *table)
{
	pthread_t	*list;
	t_uint		i;

	list = malloc(table->num_of_philo * sizeof(pthread_t));
	if (!list)
		return (-1);
	i = 0;
	table->init = philo_timer();
	while (i < table->num_of_philo)
	{
		if (pthread_create(list + i, NULL, philo_routine, table->philo + i))
		{
			free(list);
			return (-1);
		}
		monitor_mutex(LOCK);
		table->philo[i].last_eat = table->init;
		monitor_mutex(UNLOCK);
		++i;
	}
	monitor(table);
	i = 0;
	while (i < table->num_of_philo)
		pthread_mutex_destroy(&table->fork[i++]);
	i = 0;
	while (i < table->num_of_philo)
		pthread_join(list[i++], NULL);
	print_mutex(DESTROY);
	monitor_mutex(DESTROY);
	free(list);
	return (0);
}
