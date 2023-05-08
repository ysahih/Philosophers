#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
#include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include<sys/time.h>
#include<limits.h>



typedef struct	s_data
{
	int 			nb_philo;
	int 			nb_eat;
	int				count;
	unsigned long	to_die;
	unsigned long	to_eat;
	unsigned long	to_sleep;
	unsigned long	start;
	pthread_mutex_t	print;

} t_data;

typedef struct s_philo
{
	int				id;
	int				meals_taken;
	unsigned long	last_meal;
	pthread_mutex_t	fork;
	pthread_t		t;
	t_data			*info;
	struct	s_philo	*next;

} t_philo;



//list utils
void	circular(t_philo *philo);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstlast(t_philo *lst);
t_philo	*list_philos(t_data *rules);

//storing up
t_philo	*init_philos(t_data *rules, int id);
int	init_mutex(t_philo *philo);
t_data	*store_up(int ac, char **av);

//parsin
int		ft_atoi(char *str);
void	ft_error(void);
int		is_num(char *s);
int	parse(int ac, char **av);

//utils
void	ft_free(t_philo *philo);
void	error_handler(int e);
unsigned long	timeInMs(void);
void	ft_usleep(unsigned long ms, unsigned long now);
void	detach(t_philo *philo);

#endif