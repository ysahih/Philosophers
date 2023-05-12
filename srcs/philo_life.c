/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:40 by ysahih            #+#    #+#             */
/*   Updated: 2023/05/13 00:48:31 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	philos_alive(t_philo *philo){
	unsigned long	t;

	pthread_mutex_lock(&philo->meal);
	t = timeinms() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal);
	if (t > philo->info->to_die)
	{
		pthread_mutex_lock(&philo->info->print);
		printf("%lu Philosopher %d died\n",
			timeinms() - philo->info->start, philo->id);
		return (false);
	}
	return (true);
}

bool	philos_full(t_philo *philo)
{
	int	i;
	int	m;

	i = philo->info->nb_philo;
	while (i--)
	{
		pthread_mutex_lock(&philo->meals);
		m = philo->meals_taken;
		pthread_mutex_unlock(&philo->meals);
		if (m < philo->info->nb_eat)
			return (false);
		philo = philo->next;
	}
	pthread_mutex_lock(&philo->info->print);
	return (true);
}

int	create_threads(t_philo *philo)
{
	int	i;

	i = philo->info->nb_philo;
	while (i--)
	{
		if (pthread_create(&philo->t, NULL, &routine, (void *)philo))
			return (1);
		philo = philo->next;
	}
	return (0);
}
