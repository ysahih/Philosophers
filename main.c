#include "philo.h"

int i = 0;


int	init_mutex(t_data *rules)
{
	int	i;
	i = rules->nb_philo;
	while(i--)
		if (pthread_mutex_init(&rules->fork[i], NULL))
			return (1);
	if (pthread_mutex_init(&rules->print, NULL))
		return (1);
	return (0);
}

void	init_philos(t_data *rules)
{
	int	i;

	i = 0;
	i = rules->nb_philo;
	while (i--)
	{
		rules->philo[i].id = i + 1;
		rules->philo->info = rules;
		// rules->philo->fork_one[i] = i;
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



unsigned long	timeInMs(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void*	routine(void* arg)
{
	t_philo *philo;
	// int	i;

	philo  = (t_philo *)arg;

	// i = rules->nb_philo;
	// for ()
	// if (!arg)
	// 	return 0 ;
	
	// i = *(int *)arg;

	while (true)
	{
	pthread_mutex_lock (&);
	// printf("%d\n",philo->id[2]);
	// 	sleep(1);
	// for (int j = 0; j < 5; j++)
		printf("philo number %d died\n", philo->id[--i]);
	pthread_mutex_unlock (&s->print);
	}

	return NULL;
}

int	create_threads(t_data *rules)
{
	int	i;
	i = rules->philo->info->nb_philo;
	// printf("%d\n", i);
	// rules->philo->id = 10;
	// for (int j = 0; j < 5; j++)
	// 	printf("philo number %d died\n", rules->philo->id[j]);
	while (i--)
		if (pthread_create(&rules->philo->t[i], NULL, &routine, rules))
			perror("Failed to create thread");
	i = rules->philo->info->nb_philo;
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