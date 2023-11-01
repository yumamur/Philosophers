#include "philo.h"
#include "typeft.h"
#include <sched.h>
#include <sys/wait.h>
#include <signal.h>

int		set_the_table(int argc, char *argv[], t_table *table);
int		print_status(t_philo *philo, t_time *start, char statusmsg[]);
void	*routine(void *param);

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
	sem_unlink("/monitor_semaphore");
	sem_unlink("/print_semaphore");
	sem_unlink("/forks_semaphore");
	free(table->philos);
}

void	monitor(t_table *table)
{
	t_uint	i;

	while (!table->done)
	{
		i = -1;
		while (!table->death && ++i < table->num_of_philo)
		{
			sem_wait(table->monitor);
			if (nanotime() - table->philos[i].last_eat > table->time_to_die
				&& --table->death)
				printf("%lu\t%d %s\n", nanotime() - table->start, ++i, DEAD);
			sem_post(table->monitor);
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
		if (list[i])
		{
			table.philos[i].last_eat = table.start;
			routine(table.philos + i);
		}
	}
	monitor(&table);
	unset_the_table(&table, list);
	return (EXIT_SUCCESS);
}
