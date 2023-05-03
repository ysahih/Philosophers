#include "philo.h"
pthread_mutex_t x;



int	init_mutex(t_data *rules)
{
	int	i;
	i = rules->nb_philo;
	pthread_mutex_init(&x, NULL);
	while(i--)
		if (pthread_mutex_init(&rules->fork[i], NULL))
			return (1);
	if (pthread_mutex_init(&rules->print, NULL))
		return (1);
	pthread_mutex_destroy(&x);
	return (0);
}

void	init_philos(t_data *rules)
{
	int	i;

	i = rules->nb_philo;
	while (i--)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].info = rules;
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



// unsigned long	timeInMs(void)
// {
// 	struct timeval	now;

// 	gettimeofday(&now, NULL);
// 	return (now.tv_sec * 1000 + now.tv_usec / 1000);
// }

void*	routine(void* arg)
{
	t_philo	*philo;
	int		id;
	philo = (t_philo *)arg;
	id = philo->id;

// pthread_mutex_lock(&philo->info->fork[philo->id]);
	// printf("%d\n", id);
// pthread_mutex_unlock(&philo->info->fork[philo->id]);
	
	int		fork_one = id - 1;
	int		fork_two = id % philo->info->nb_philo;

	while (true){
        // Think for a while
        printf("Philosopher %d is thinking\n", id);
        usleep(rand() % 1000000);

        // Pick up left chopstick
        pthread_mutex_lock(&philo->info->fork[fork_one]);
        printf("Philosopher %d picked up left chopstick %d\n", id, fork_one);

        // Pick up right chopstick
        pthread_mutex_lock(&philo->info->fork[fork_two]);
        printf("Philosopher %d picked up right chopstick %d\n", id, fork_two);

        // Eat for a while
        printf("Philosopher %d is eating\n", id);
        usleep(rand() % 1000000);

        // Put down right chopstick
        pthread_mutex_unlock(&philo->info->fork[fork_one]);
        printf("Philosopher %d put down right chopstick %d\n", id, fork_one);

        // Put down left chopstick
        pthread_mutex_unlock(&philo->info->fork[fork_two]);
        printf("Philosopher %d put down left chopstick %d\n", id, fork_two);
    }
	// free(philo);
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
	
	if (parse(ac, av) == 0){
		return (ft_error(),0);
	}
	init_mutex(&rules);

	if (!init(&rules, ac, av)){
		return (ft_error(),0);
	}
	// for (int j = 0; j < 5; j++)
	// 	printf("philo number %d died\n", rules.philo->id[j]);
	create_threads(&rules);
	// rules.nb_philo
}