#include "philo.h"


// t_philo	*ft_lstlast(t_philo *lst)
// {
// 	if (!lst)
// 		return (0);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }

// void	ft_lstadd_back(t_philo **lst, t_philo *new)
// {
// 	t_philo	*last_node;

// 	if (!lst)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last_node = ft_lstlast(*lst);
// 	last_node->next = new;
// }

// void	circular(t_philo *philo)
// {
// 	t_philo	*tmp;

// 	tmp = philo;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = philo;
// }


int	init_mutex(t_philo *philo)
{
	int	i;
	i = philo->info->nb_philo;
	// rules->philo->fork = malloc (sizeof(pthread_mutex_t) * i);
	while(i--){
		if (pthread_mutex_init(&philo->fork, NULL))
			return (1);
		philo = philo->next;
	}
	if (pthread_mutex_init(&philo->info->print, NULL))
		return (1);
	return (0);
}

// unsigned long	timeInMs(void)
// {
// 	struct timeval	now;

// 	gettimeofday(&now, NULL);
// 	return (now.tv_sec * 1000 + now.tv_usec / 1000);
// }

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
	philo->next = NULL;
	return (philo);
}

t_data	*store_up(int ac, char **av)
{
	if (!parse(ac, av))
		return (NULL);
	t_data *rules = malloc(sizeof(t_data));
	
	rules->nb_philo = ft_atoi(av[1]);
	rules->to_die = ft_atoi(av[2]);
	rules->to_eat = ft_atoi(av[3]);
	rules->to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		rules->nb_eat = ft_atoi(av[5]);
	else if (ac == 5)
		rules->nb_eat = -1;
	// init_philos(rules);
	return (rules);
}

// void	feed_philo(t_philo *philo)
// {
	
// 	philo->info->last_meal = timeInMs();
    
//     pthread_mutex_lock(&philo->print);
//     printf("%lu Philosopher %d is eating\n", timeInMs(), philo->id);
//     pthread_mutex_unlock(&philo->print);
// 	usleep(philo->info->to_eat * 1000);
	
// }

// bool	philos_alive(t_philo *philo)
// {
// 	unsigned long	time_since_last_meal;

// 	time_since_last_meal = timeInMs() - philo->info->last_meal;
// 	if (time_since_last_meal > philo->info->to_eat)
// 	{
// 		pthread_mutex_lock(&philo->print);
// 		printf("%lu Philosopher %d died\n", timeInMs(), philo->id);
// 		pthread_mutex_unlock(&philo->print);
// 		return (false);
// 	}
// 	return (true);
// }

// void*	routine(void* arg)
// {
// 	t_philo	*philo;
// 	int		id;
// 	philo = (t_philo *)arg;
// 	id = philo->id;

// 	int	fork1 = id;
// 	int	fork2 = (id + 1) % philo->info->nb_philo;

// 	puts("here");

// 	while (true) {
//         if (!philos_alive(philo)) {
//             return 0;
//         }
//         pthread_mutex_lock(&philo->fork[fork1]);
//         pthread_mutex_lock(&philo->fork[fork2]);

//         pthread_mutex_lock(&philo->print);
//         printf("%lu Philosopher %d has taken a fork\n", timeInMs(), philo->id);
//         printf("%lu Philosopher %d has taken a fork\n", timeInMs(), philo->id);
//         pthread_mutex_unlock(&philo->print);

// 		feed_philo(philo);

//         pthread_mutex_unlock(&philo->fork[fork1]);
//         pthread_mutex_unlock(&philo->fork[fork2]);

//         pthread_mutex_lock(&philo->print);
//         printf("%lu Philosopher %d is sleeping\n", timeInMs(), philo->id );
//         pthread_mutex_unlock(&philo->print);
//         usleep(philo->info->to_sleep * 1000);

// 		pthread_mutex_lock(&philo->print);
//         printf("%lu Philosopher %d is thinking\n", timeInMs(), philo->id );
//         pthread_mutex_unlock(&philo->print);

//     }
//     return NULL;
// }


// int	create_threads(t_data *rules)
// {
// 	int	i;
// 	i = rules->nb_philo;

// 	while (i--){
// 		t_philo *philo = malloc (sizeof(t_philo));
// 		philo = &rules->philo[i];
// 		if (pthread_create(&rules->philo->t[i], NULL, &routine, (void *)philo))
// 			perror("Failed to create thread");
// 	}
// 	i = rules->nb_philo;
// 	while (i--)
// 		if (pthread_join(rules->philo->t[i], NULL))
// 			return (1);
// 	return (0);
// }

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

// void	ft_test(t_philo	*philo)
// {
// 	int i = philo->info->nb_philo;
// 	while (philo)
// 	{
// 		printf("%d\n", philo->id);
// 		philo = philo->next;
// 	}
// }

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
	
	// ft_test(philo);
	// puts("hh");
	// philo = init_philos()
	// // init_mutex(&rules);
	// // puts("here");
	// // }
	// create_threads(&rules);
	// pthread_mutex_destroy(&rules.philo->print);
	// int i = rules.nb_philo;
	// while (i--)
	// 	pthread_mutex_destroy(&rules.philo->fork[i]);


}