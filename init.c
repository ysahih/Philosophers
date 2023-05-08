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
	rules->count = 0;

	if (ac == 6)
		rules->nb_eat = ft_atoi(av[5]);
	else if (ac == 5)
		rules->nb_eat = -1;
	return (rules);
}


