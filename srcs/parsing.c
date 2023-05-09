/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:37 by ysahih            #+#    #+#             */
/*   Updated: 2023/05/09 00:52:38 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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

int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int	parse(int ac, char **av)
{
	int		i;
	int		j;

	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!is_num(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_error(void)
{
	printf("Wrong Args");
}
