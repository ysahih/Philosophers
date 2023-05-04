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
	unsigned long	to_die;
	unsigned long	to_eat;
	unsigned long	to_sleep;
	unsigned long	last_meal;
	int 			nb_eat;
	struct s_philo	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;

} t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	fork_one;
	pthread_mutex_t	fork_two;
	pthread_t		t[200];
	t_data			*info;

} t_philo;


//parsin
int		ft_atoi(char *str);
void	ft_error(void);
int		is_num(char *s);
int		parse(int ac, char **av);

#endif