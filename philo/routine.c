/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumamur <yumamur@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 19:51:23 by yumamur           #+#    #+#             */
/*   Updated: 2023/10/31 19:51:23 by yumamur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "philo_types.h"

int	print_status(t_philo *philo, t_time *start, char statusmsg[])
{
	pthread_mutex_lock(&philo->table->print);
	if (!philo->table->death && !philo->table->done)
		printf("%lu\t%d %s\n", nanotime() - *start, philo->seat, statusmsg);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

static void	eat(t_philo *philo, t_time *start)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, start, FORK);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, start, FORK);
	pthread_mutex_lock(&philo->table->monitor);
	++philo->ct_of_eat;
	print_status(philo, start, EAT);
	philo->last_eat = nanotime();
	pthread_mutex_unlock(&philo->table->monitor);
	p_sleep(&philo->table->death, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->seat % 2 == 0)
		usleep(1000);
	while (!table->done && !table->death)
	{
		eat(philo, &table->start);
		print_status(philo, &table->start, SLEEP);
		p_sleep(&philo->table->death, philo->table->time_to_sleep);
		print_status(philo, &table->start, THINK);
		usleep(500);
	}
	return (NULL);
}
