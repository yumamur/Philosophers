/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumamur <yumamur@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:34:40 by yumamur           #+#    #+#             */
/*   Updated: 2023/10/31 19:34:40 by yumamur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		set_the_table(int argc, char *argv[], t_table *table);
int		print_status(t_philo *philo, t_time *start, char statusmsg[]);
void	*routine(void *param);

void	unset_the_table(t_table *table, pthread_t *list)
{
	t_uint	i;

	i = -1;
	while (++i < table->num_of_philo)
		pthread_join(list[i], NULL);
	free(list);
	i = -1;
	while (++i < table->num_of_philo)
		pthread_mutex_destroy(table->forks + i);
	free(table->philos);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->monitor);
}

void	monitor(t_table *table)
{
	t_uint	i;

	while (!table->done)
	{
		i = -1;
		while (!table->death && ++i < table->num_of_philo)
		{
			pthread_mutex_lock(&table->monitor);
			if (nanotime() - table->philos[i].last_eat > table->time_to_die
				&& --table->death)
				printf("%lu\t%d %s\n", nanotime() - table->start, ++i, DEAD);
			pthread_mutex_unlock(&table->monitor);
			usleep(100);
		}
		if (table->death)
			return ;
		i = -1;
		while (table->min_num_of_eat != -1 && ++i < table->num_of_philo
			&& table->philos[i].ct_of_eat >= table->min_num_of_eat)
			;
		if (i == table->num_of_philo)
			table->done = -1;
	}
}

int	main(int argc, char *argv[])
{
	t_table		table;
	pthread_t	*list;
	t_uint		i;

	if (set_the_table(argc, argv, &table))
		return (EXIT_FAILURE);
	list = malloc(table.num_of_philo * sizeof(*list));
	table.start = nanotime();
	i = -1;
	while (++i < table.num_of_philo)
	{
		if (pthread_create(list + i, NULL, routine, table.philos + i))
		{
			free(list);
			free(table.philos);
			return (EXIT_FAILURE);
		}
		table.philos[i].last_eat = table.start;
	}
	monitor(&table);
	unset_the_table(&table, list);
	return (EXIT_SUCCESS);
}
