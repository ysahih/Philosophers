#include "../philo.h"

void	feed_philo(t_philo *philo)
{
	philo->last_meal = timeInMs();
	pthread_mutex_lock(&philo->info->print);
	printf("%lu Philosopher %d is eating\n", timeInMs() - philo->info->start, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	philo->meals_taken++;
	philo->info->count++;
	if (philo->info->count > philo->info->nb_philo)
		philo->info->count = 1;
	ft_usleep(philo->info->to_eat * 1000, timeInMs());
}

void	print_status(t_philo *philo )
{
	pthread_mutex_lock(&philo->info->print);
	printf("%lu Philosopher %d has taken a fork\n", timeInMs() - philo->info->start, philo->id);
	pthread_mutex_unlock(&philo->info->print);
}

void	feed_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_status(philo);
	pthread_mutex_lock(&philo->next->fork);
	print_status(philo);
	feed_philo(philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	feed_even(t_philo *philo)
{
	usleep(200);
	pthread_mutex_lock(&philo->next->fork);
	print_status(philo);
	pthread_mutex_lock(&philo->fork);
	print_status(philo);
	feed_philo(philo);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
}