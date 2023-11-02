/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumamur <yumamur@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:17:24 by yumamur           #+#    #+#             */
/*   Updated: 2023/11/01 13:17:24 by yumamur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo_bonus.h"

int	print_status(t_philo *philo, t_time *start, char statusmsg[])
{
	if (philo->table->death || philo->table->done)
		return (-1);
	sem_wait(philo->table->print);
	printf("%lu\t%d %s\n", nanotime() - *start, philo->seat, statusmsg);
	sem_post(philo->table->print);
	return (0);
}

static int	eat(t_philo *philo, t_time *start)
{
	sem_wait(philo->table->forks);
	if (print_status(philo, start, FORK))
		return (-1);
	sem_wait(philo->table->forks);
	if (print_status(philo, start, FORK))
		return (-1);
	++philo->ct_of_eat;
	if (print_status(philo, start, EAT))
		return (-1);
	philo->last_eat = nanotime();
	if (p_sleep(&philo->table->death, philo->table->time_to_eat))
		return (-1);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
	return (0);
}

void	*monitor(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->table->monitor);
		if (nanotime() - philo->last_eat > philo->table->time_to_die)
		{
			sem_wait(philo->table->print);
			printf("%lu\t%d is dead\n", nanotime() - philo->table->start,
				philo->seat);
			philo->table->death = -1;
			exit(1);
		}
		sem_post(philo->table->monitor);
		usleep(1000);
		if (philo->table->min_num_of_eat != -1
			&& philo->ct_of_eat >= philo->table->min_num_of_eat)
			break ;
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	philo->last_eat = table->start;
	pthread_create(&philo->monitor, NULL, (void *(*)(void *))monitor, philo);
	while (!table->done && !table->death)
	{
		if (eat(philo, &table->start))
			break ;
		if (philo->table->min_num_of_eat != -1
			&& philo->ct_of_eat >= philo->table->min_num_of_eat)
			break ;
		if (print_status(philo, &table->start, SLEEP))
			break ;
		if (p_sleep(&table->death, table->time_to_sleep))
			break ;
		if (print_status(philo, &table->start, THINK))
			break ;
	}
	pthread_join(philo->monitor, NULL);
	exit(0);
}
