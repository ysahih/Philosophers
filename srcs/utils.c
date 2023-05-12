/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:45 by ysahih            #+#    #+#             */
/*   Updated: 2023/05/13 00:48:28 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_free(t_philo *philo){
	int		n;
	t_philo	*tmp;

	n = philo->info->nb_philo;
	free(philo->info);
	while (n-- && philo)
	{
		tmp = philo;
		philo = philo->next;
		free(tmp);
	}
}

void	detach(t_philo *philo)
{
	int	i;

	i = philo->info->nb_philo;
	pthread_mutex_unlock(&philo->info->print);
	pthread_mutex_unlock(&philo->meals);
	pthread_mutex_destroy(&philo->info->print);
	while (i--)
	{
		pthread_detach(philo->t);
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
	}
}

void	error_handler(int e)
{
	if (e == 1)
		printf("Failed to create mutex!");
	if (e == 2)
		printf("Failed to create threrad!");
}

unsigned long	timeinms(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	ft_usleep(unsigned long ms, unsigned long now)
{
	usleep(ms * 0.95);
	while (timeinms() < (now + ms / 1000))
		usleep(100);
}
