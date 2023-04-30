#include "philo.h"

void *i = "A";


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
		
		rules->philo->id[i] = i;
		rules->philo->info = rules;
		rules->philo->fork[i] = i;
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



void*	routine(void* arg)
{
	// if (!arg)
	// 	return 0 ;
	// t_philo *philo;
	// philo  = (t_philo *)arg;
	// printf("%d\n",philo->fork[1]);
	// // (void *)i;

	while (true)
	{
		printf("")
	}
	return NULL;
}

int	create_threads(t_data *rules)
{
	int	i;
	i = rules->philo->info->nb_philo;
	// rules->philo->id = 10;
	while (i--)
		if (pthread_create(&rules->philo->t[i], NULL, &routine, rules->philo))
			return (1);
	i = rules->philo->info->nb_philo;
	while (i--)
		if (pthread_join(rules->philo->t[i], (void *)rules->philo))
			return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		rules;

	if (parse(ac, av) == 0)
		return (ft_error(),0);
	if (!init(&rules, ac, av))
		return (ft_error(),0);
	// for (int i = 0; i < 5; i++)
	// 	printf("%d\n", rules.philo->id[i]);
	create_threads(&rules);
	
	// printf("%d\n", rules.nb_philo);
	// rules.nb_philo
}