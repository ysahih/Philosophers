/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:29 by ysahih            #+#    #+#             */
/*   Updated: 2023/05/13 00:48:47 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_mutex(t_philo *philo){
	int	i;

	i = philo->info->nb_philo;
	while (i--)
	{
		if (pthread_mutex_init(&philo->fork, NULL))
			return (1);
		if (pthread_mutex_init(&philo->meal, NULL))
			return (1);
		if (pthread_mutex_init(&philo->meals, NULL))
			return (1);
		philo = philo->next;
	}
	if (pthread_mutex_init(&philo->info->print, NULL))
		return (1);
	return (0);
}

t_philo	*init_philos(t_data *rules, int id)
{
	int		i;
	t_philo	*philo;

	i = rules->nb_philo;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id + 1;
	philo->info = rules;
	philo->meals_taken = 0;
	philo->last_meal = timeinms();
	philo->next = NULL;
	return (philo);
}

t_data	*store_up(int ac, char **av)
{
	t_data	*rules;

	if (!parse(ac, av))
		return (ft_error(), NULL);
	rules = malloc(sizeof(t_data));
	rules->nb_philo = ft_atoi(av[1]);
	if (rules->nb_philo == 0)
		return (NULL);
	rules->to_die = ft_atoi(av[2]);
	rules->to_eat = ft_atoi(av[3]);
	rules->to_sleep = ft_atoi(av[4]);
	rules->start = timeinms();
	if (ac == 6)
		rules->nb_eat = ft_atoi(av[5]);
	else if (ac == 5)
		rules->nb_eat = INT_MAX;
	return (rules);
}
