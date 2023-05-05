#include "philo.h"



int	init_mutex(t_data *rules)
{
	int	i;
	i = rules->nb_philo;
	rules->philo->fork = malloc (sizeof(pthread_mutex_t) * i);
	while(i--){
		if (pthread_mutex_init(&rules->philo->fork[i], NULL))
			return (1);
	}
	if (pthread_mutex_init(&rules->philo->print, NULL))
		return (1);

	puts("here");
	return (0);
}

unsigned long	timeInMs(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	init_philos(t_data *rules)
{
	int	i;

	i = rules->nb_philo;
	
	while (i--)
	{
		// printf("%d\n", i);
		rules->philo[i].id = i + 1;
	
		rules->philo[i].info = rules;
		
		// rules->philo[i].fork_two = rules->philo[(i + 1) % rules->nb_philo].fork_one;

		// rules->philo[i].fork_two = rules->philo[(i + 1) % rules->nb_philo].fork_one;
		rules->philo->info->last_meal = timeInMs();
	}
}

int	init(t_data *rules, int ac, char **av)
{
	rules->nb_philo = ft_atoi(av[1]);
	rules->to_die = ft_atoi(av[2]);
	rules->to_eat = ft_atoi(av[3]);
	rules->to_sleep = ft_atoi(av[4]);

	
	if (ac == 6)
		rules->nb_eat = ft_atoi(av[5]);
	if (rules->nb_philo > 200)
		return (0);
	init_philos(rules);
	return (1);
}

void	feed_philo(t_philo *philo)
{
	
	philo->info->last_meal = timeInMs();
    
    pthread_mutex_lock(&philo->print);
    printf("%lu Philosopher %d is eating\n", timeInMs(), philo->id);
    pthread_mutex_unlock(&philo->print);
	usleep(philo->info->to_eat * 1000);
	
}

bool	philos_alive(t_philo *philo)
{
	unsigned long	time_since_last_meal;

	time_since_last_meal = timeInMs() - philo->info->last_meal;
	if (time_since_last_meal > philo->info->to_eat)
	{
		pthread_mutex_lock(&philo->print);
		printf("%lu Philosopher %d died\n", timeInMs(), philo->id);
		pthread_mutex_unlock(&philo->print);
		return (false);
	}
	return (true);
}

void*	routine(void* arg)
{
	t_philo	*philo;
	int		id;
	philo = (t_philo *)arg;
	id = philo->id;

	int	fork1 = id;
	int	fork2 = (id + 1) % philo->info->nb_philo;

	puts("here");

	while (true) {
        if (!philos_alive(philo)) {
            return 0;
        }
        pthread_mutex_lock(&philo->fork[fork1]);
        pthread_mutex_lock(&philo->fork[fork2]);

        pthread_mutex_lock(&philo->print);
        printf("%lu Philosopher %d has taken a fork\n", timeInMs(), philo->id);
        printf("%lu Philosopher %d has taken a fork\n", timeInMs(), philo->id);
        pthread_mutex_unlock(&philo->print);

		feed_philo(philo);

        pthread_mutex_unlock(&philo->fork[fork1]);
        pthread_mutex_unlock(&philo->fork[fork2]);

        pthread_mutex_lock(&philo->print);
        printf("%lu Philosopher %d is sleeping\n", timeInMs(), philo->id );
        pthread_mutex_unlock(&philo->print);
        usleep(philo->info->to_sleep * 1000);

		pthread_mutex_lock(&philo->print);
        printf("%lu Philosopher %d is thinking\n", timeInMs(), philo->id );
        pthread_mutex_unlock(&philo->print);

    }
    return NULL;
}


int	create_threads(t_data *rules)
{
	int	i;
	i = rules->nb_philo;

	while (i--){
		t_philo *philo = malloc (sizeof(t_philo));
		philo = &rules->philo[i];
		if (pthread_create(&rules->philo->t[i], NULL, &routine, (void *)philo))
			perror("Failed to create thread");
	}
	i = rules->nb_philo;
	while (i--)
		if (pthread_join(rules->philo->t[i], NULL))
			return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		rules;
	
	rules.philo = malloc(sizeof(t_philo));
	if (parse(ac, av) == 0){
		return (ft_error(),0);
	}
	init_mutex(&rules);

	if (!init(&rules, ac, av)){
		return (ft_error(),0);
	// puts("here");
	}
	create_threads(&rules);
	pthread_mutex_destroy(&rules.philo->print);
	int i = rules.nb_philo;
	while (i--)
		pthread_mutex_destroy(&rules.philo->fork[i]);


}