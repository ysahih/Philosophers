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
	unsigned long	to_die;
	unsigned long	to_eat;
	unsigned long	to_sleep;
	unsigned long	last_meal;
	struct s_philo	*philo;
	pthread_mutex_t	print;

} t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	fork;
	pthread_t		t;
	t_data			*info;
	struct	s_philo	*next;

} t_philo;



//list utils
void	circular(t_philo *philo);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstlast(t_philo *lst);

//parsin

int		ft_atoi(char *str);
void	ft_error(void);
int		is_num(char *s);
int	parse(int ac, char **av);

#endif