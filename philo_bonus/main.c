#include "philo.h"

int	init_table(int argc, char *argv[], t_table *table);
int	set_the_table(t_table *table);
int	unset_the_table(t_table *table);
int	usher_philosophers(t_table *table);
int	let_the_feast_begin(t_table *table);

int	main(int argc, char *argv[])
{
	t_table	table;

	table = (t_table){};
	if (init_table(argc, argv, &table))
		return (0);
	if (set_the_table(&table))
		return (-1);
	if (let_the_feast_begin(&table))
		return (-1);
	if (unset_the_table(&table))
		return (-1);
}
