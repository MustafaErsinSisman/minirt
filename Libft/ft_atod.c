

#include "libft.h"

double	ft_atod(const char *str, size_t i, int sign)
{
	double	nb;
	double	frac;

	nb = 0.0;
	frac = 0.1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = (str[i++] - '0') + (nb * 10.0);
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			nb = nb + (str[i++] - '0') * frac;
			frac *= 0.1;
		}
	}
	return (nb * sign);
}
