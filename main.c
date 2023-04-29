#include "philo.h"


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
		rules->philo->id = i;
		rules->philo->info = rules;
		rules->philo->fork = i;
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



void	routine(void *philo)
{
	void *s;
	s = "hello";
	printf("%s\n", s);
	// return s;
}

int	create_threads(t_data *rules)
{
	int	i;
	i = rules->philo->info->nb_philo;
	while (i--)
		if (pthread_create(&rules->philo->t, NULL, &routine, rules->philo))
			return (1);
	i = rules->philo->info->nb_philo;
	while (i--)
		if (pthread_join(rules->philo->t, NULL))
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
	
	// printf("%d\n", rules.nb_philo);
	// rules.nb_philo
}