#include "philo.h"

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



void	feed_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	
	pthread_mutex_lock(&philo->info->print);
	printf("%lu Philosopher %d has taken a fork\n", timeInMs() - philo->info->start, philo->id);
	pthread_mutex_unlock(&philo->info->print);

	pthread_mutex_lock(&philo->next->fork);
	
	pthread_mutex_lock(&philo->info->print);
	printf("%lu Philosopher %d has taken a fork\n", timeInMs() - philo->info->start, philo->id);
	pthread_mutex_unlock(&philo->info->print);

	feed_philo(philo);

	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);	
}

void	feed_even(t_philo *philo)
{
	
	usleep(200);
	pthread_mutex_lock(&philo->next->fork);

	pthread_mutex_lock(&philo->info->print);
	printf("%lu Philosopher %d has taken a fork\n", timeInMs() - philo->info->start, philo->id);
	pthread_mutex_unlock(&philo->info->print);

	pthread_mutex_lock(&philo->fork);

	pthread_mutex_lock(&philo->info->print);
	printf("%lu Philosopher %d has taken a fork\n", timeInMs() - philo->info->start, philo->id);
	pthread_mutex_unlock(&philo->info->print);

	feed_philo(philo);

	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
}

void*	routine(void* arg)
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
		printf("%lu Philosopher %d is sleeping\n", timeInMs() - philo->info->start, philo->id );
		pthread_mutex_unlock(&philo->info->print);
		
		ft_usleep(philo->info->to_sleep * 1000, timeInMs());

		pthread_mutex_lock(&philo->info->print);
		printf("%lu Philosopher %d is thinking\n", timeInMs() - philo->info->start, philo->id);
		pthread_mutex_unlock(&philo->info->print);
	}
	return NULL;
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

void	fun()
{
	system("leaks philo");
}


bool	philos_full(t_philo *philo)
{
	int	i;

	i = philo->info->nb_philo;
	while (i--)
	{
		if (philo->meals_taken != philo->info->nb_eat)
			return (false);
		philo = philo->next;
	}
	pthread_mutex_lock(&philo->info->print);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	*rules;
	t_philo	*philo;

	atexit(fun);
	rules = store_up(ac, av);
	if (!rules)
		return (0);
	philo = list_philos(rules);
	if (!philo)
		return (0);
	if(init_mutex(philo))
		return (error_handler(1), 0);
	if(create_threads(philo))
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