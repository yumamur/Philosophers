#include "philo.h"

int	parse_args(t_philo_data *data, int argc, char *argv[]);
int	create_data(t_philo_data *data);

int	main(int argc, char *argv[])
{
	t_philo_data	data;

	if (parse_args(&data, argc, argv) || create_data(&data))
		return (0);
}
