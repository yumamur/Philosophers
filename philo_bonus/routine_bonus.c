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

#include "philo_bonus.h"

int	print_status(t_philo *philo, t_time *start, char statusmsg[])
{
	if (philo->table->death || philo->table->done)
		exit(0);
	sem_wait(philo->table->print);
	printf("%lu\t%d %s\n", nanotime() - *start, philo->seat, statusmsg);
	sem_post(philo->table->print);
	return (0);
}

static void	eat(t_philo *philo, t_time *start)
{
	sem_wait(philo->table->forks);
	print_status(philo, start, FORK);
	sem_wait(philo->table->forks);
	print_status(philo, start, FORK);
	sem_wait(philo->table->monitor);
	++philo->ct_of_eat;
	print_status(philo, start, EAT);
	philo->last_eat = nanotime();
	sem_post(philo->table->monitor);
	p_sleep(&philo->table->death, philo->table->time_to_eat);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	*routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	while (!table->done && !table->death)
	{
		eat(philo, &table->start);
		print_status(philo, &table->start, SLEEP);
		p_sleep(&table->death, table->time_to_sleep);
		print_status(philo, &table->start, THINK);
		p_sleep(&table->death,
			(table->time_to_die - (nanotime() - philo->last_eat)) / 2);
	}
	exit(0);
}
