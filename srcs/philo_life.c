#include "../philo.h"

bool	philos_alive(t_philo *philo)
{
	unsigned long	time_since_last_meal;

	time_since_last_meal = timeInMs() - philo->last_meal;
	if (time_since_last_meal > philo->info->to_die)
	{
		pthread_mutex_lock(&philo->info->print);
		printf("%lu Philosopher %d died\n", timeInMs() - philo->info->start, philo->id);
		return (false);
	}
	return (true);
}

bool	philos_full(t_philo *philo)
{
	int	i;

	i = philo->info->nb_philo;
	while (i--)
	{
		if (philo->meals_taken < philo->info->nb_eat)
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
	while (i--){
		if (pthread_create(&philo->t, NULL, &routine, (void *)philo))
			return (1);
		philo = philo->next;
	}
	return (0);
}