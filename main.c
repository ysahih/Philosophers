/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:49 by ysahih            #+#    #+#             */
/*   Updated: 2023/05/12 23:40:14 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)arg;
	id = philo->id;
	while (true)
	{
		if (philo->id % 2 != 0)
			feed_odd(philo);
		else
			feed_even(philo);
		pthread_mutex_lock(&philo->info->print);
		printf("%lu Philosopher %d is sleeping\n",
			timeinms() - philo->info->start, philo->id);
		pthread_mutex_unlock(&philo->info->print);
		ft_usleep(philo->info->to_sleep * 1000, timeinms());
		pthread_mutex_lock(&philo->info->print);
		printf("%lu Philosopher %d is thinking\n",
			timeinms() - philo->info->start, philo->id);
		pthread_mutex_unlock(&philo->info->print);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*rules;
	t_philo	*philo;

	rules = store_up(ac, av);
	if (!rules)
		return (0);
	philo = list_philos(rules);
	if (!philo)
		return (0);
	if (init_mutex(philo))
		return (error_handler(1), 0);
	if (create_threads(philo))
		return (error_handler(2), 0);
	while (true)
	{
		if (!philos_alive(philo) || philos_full(philo))
		{
			detach(philo);
			return (0);
		}
		philo = philo->next;
	}
}
