#include "philo.h"

int	init_mutex(t_philo *philo)
{
	int	i;
	i = philo->info->nb_philo;
	while(i--){
		if (pthread_mutex_init(&philo->fork, NULL))
			return (1);
		philo = philo->next;
	}
	if (pthread_mutex_init(&philo->info->print, NULL))
		return (1);
	return (0);
}

unsigned long	timeInMs(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
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
	philo->last_meal = timeInMs();
	philo->next = NULL;
	return (philo);
}

t_data	*store_up(int ac, char **av)
{
	if (!parse(ac, av))
		return (ft_error(), NULL);
	t_data *rules = malloc(sizeof(t_data));
	
	rules->nb_philo = ft_atoi(av[1]);
	rules->to_die = ft_atoi(av[2]);
	rules->to_eat = ft_atoi(av[3]);
	rules->to_sleep = ft_atoi(av[4]);
	rules->start = timeInMs();
	if (ac == 6)
		rules->nb_eat = ft_atoi(av[5]);
	else if (ac == 5)
		rules->nb_eat = -1;
	return (rules);
}

void	ft_usleep(unsigned long ms, unsigned long now)
{
	usleep(ms * 0.95);
	while (timeInMs() < (now + ms / 1000))
		usleep(100);	
}

void	feed_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print);
	printf("%lu Philosopher %d is eating\n", timeInMs() - philo->info->start, philo->id);
	pthread_mutex_unlock(&philo->info->print);
	philo->meals_taken++;
	ft_usleep(philo->info->to_eat * 1000, timeInMs());
	
	philo->last_meal = timeInMs();
}

bool	philos_alive(t_philo *philo)
{
	unsigned long	time_since_last_meal;

	time_since_last_meal = timeInMs() - philo->last_meal;
	// printf("id : %d, ->%lu\n",philo->id, time_since_last_meal);
	// printf("%lu\n", philo->info->to_eat);

	if (time_since_last_meal > philo->info->to_die)
	{
		pthread_mutex_lock(&philo->info->print);
		printf("%lu Philosopher %d died\n", timeInMs() - philo->info->start, philo->id);
		pthread_mutex_unlock(&philo->info->print);
		return (false);
	}
	return (true);
}


void	feed_even(t_philo *philo)
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

void*	routine(void* arg)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)arg;
	id = philo->id;

	while (true) 
	{

		if (philo->id % 2)
			feed_even(philo);
		else
		{
			ft_usleep(1, timeInMs());
			pthread_mutex_lock(&philo->next->fork);

			pthread_mutex_lock(&philo->info->print);
			printf("%lu Philosopher %d has taken a fork\n", timeInMs() - philo->info->start, philo->id);
			pthread_mutex_lock(&philo->fork);
			printf("%lu Philosopher %d has taken a fork\n", timeInMs() - philo->info->start, philo->id);
			pthread_mutex_unlock(&philo->info->print);

			feed_philo(philo);

			pthread_mutex_unlock(&philo->next->fork);
			pthread_mutex_unlock(&philo->fork);
		}

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
		// t_philo *philo = malloc (sizeof(t_philo));
		// philo = &rules->philo[i];
		if (pthread_create(&philo->t, NULL, &routine, (void *)philo))
			return (1);
		philo = philo->next;
	}
	// i = philo->info->nb_philo;
	// while (i--)
	// 	if (pthread_join(philo->t, NULL))
	// 		return (1);
	return (0);
}

t_philo	*list_philos(t_data *rules)
{
	t_philo	*philo;
	t_philo	*node;
	int		i;

	i = rules->nb_philo;
	philo = NULL;
	while(i--)
	{
		node = init_philos(rules, i);
		if (!node)
			return (NULL);
		ft_lstadd_back(&philo, node);
	}
	circular(philo);
	return (philo);
}

void	ft_free(t_philo *philo)
{
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
	// free(philo);
}

void	error_handler(int e)
{
	if (e == 1)
		printf("Failed to create mutex!");
	if (e == 1)
		printf("Failed to create threrad!");
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
	if(init_mutex(philo))
		return (error_handler(1), 0);
	
	if(create_threads(philo))
		return (error_handler(2), 0);
		
	while (true)
	{
		if (!philos_alive(philo) || (philo->meals_taken == philo->info->nb_eat))
		{
			ft_free(philo);
			return (0);
		}
		philo = philo->next;
	}

	pthread_mutex_destroy(&philo->info->print);
	int i = philo->info->nb_philo;
	while (i--)
	{
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next;
	}
	ft_free(philo);
}