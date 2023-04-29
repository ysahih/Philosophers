#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] && (str[i] == 32))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (res * sign);
}

int	is_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' && s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	while (av[i])
	{
		if (!is_num(av[i]) || ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

void	ft_error(void)
{
	printf("Wrong Args");
}
