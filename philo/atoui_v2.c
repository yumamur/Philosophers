#include "typeft.h"
#include "limitsft.h"

int	atoui_v2(t_c_char *str, t_uint *ptr)
{
	t_ulong	ret;
	t_uint	i;

	if (!str || !*str)
		return (-1);
	i = 0;
	ret = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = (str[i] - 48) + (ret * 10);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	if (ret > INT_MAX)
		return (-1);
	*ptr = ret;
	return (0);
}
