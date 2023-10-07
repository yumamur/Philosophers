#include "philo.h"

int	parse_args(t_data *data, int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	t_data	data;

	if (parse_args(&data, argc, argv))
		return (0);
}

typedef char	t_bit8[8];
