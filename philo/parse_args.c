#include "philo_datatypes.h"

int	atoui_v2(t_c_char *str, t_uint *ptr);

int	parse_args(t_data *data, int argc, t_c_char **argv)
{
	if (argc != 5 && argc != 6)
		return (-1);
	if (atoui_v2(argv[1], &data->num_of_philo))
		return (-1);
	if (atoui_v2(argv[2], &data->time_to_die))
		return (-1);
	if (atoui_v2(argv[3], &data->time_to_eat))
		return (-1);
	if (atoui_v2(argv[4], &data->time_to_sleep))
		return (-1);
	if (argc == 6 && atoui_v2(argv[5], &data->min_ct_of_eat))
		return (-1);
	return (0);
}
