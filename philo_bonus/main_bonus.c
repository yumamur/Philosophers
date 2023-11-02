/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumamur <yumamur@student.42istanbul.com.t  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:15:49 by yumamur           #+#    #+#             */
/*   Updated: 2023/11/01 13:15:49 by yumamur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <signal.h>
#include "philo_bonus.h"

int		set_the_table(int argc, char *argv[], t_table *table);
int		print_status(t_philo *philo, t_time *start, char statusmsg[]);
void	routine(t_philo *philo);

void	unset_the_table(t_table *table, pid_t *list)
{
	t_uint	i;
	int		wstatus;

	i = -1;
	while (++i < table->num_of_philo)
	{
		waitpid(-1, &wstatus, 0);
		if (WEXITSTATUS(wstatus) == 1)
		{
			i = -1;
			while (++i < table->num_of_philo)
				kill(list[i], SIGTERM);
			break ;
		}
	}
	sem_close(table->monitor);
	sem_close(table->print);
	sem_close(table->forks);
	sem_unlink("monitor_semaphore");
	sem_unlink("print_semaphore");
	sem_unlink("forks_semaphore");
	free(table->philos);
}

int	main(int argc, char *argv[])
{
	t_table	table;
	pid_t	*list;
	t_uint	i;

	if (set_the_table(argc, argv, &table))
		return (EXIT_FAILURE);
	list = malloc(table.num_of_philo * sizeof(pid_t));
	table.start = nanotime();
	i = -1;
	while (++i < table.num_of_philo)
	{
		list[i] = fork();
		if (list[i] == -1)
			exit(1);
		if (!list[i])
			routine(table.philos + i);
	}
	unset_the_table(&table, list);
	return (EXIT_SUCCESS);
}
