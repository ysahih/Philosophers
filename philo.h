#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
#include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
#include <time.h>
#include <stdbool.h>

typedef struct	s_data
{
	int 			nb_philo;
	int				to_die;
	int 			to_eat;
	int 			to_sleep;
	int 			nb_eat;
	struct s_philo	*philo;
	pthread_mutex_t	fork[200];
	pthread_mutex_t	print;

} t_data;

typedef struct s_philo
{
	int			id[200];
	int			fork[200];
	pthread_t	t[200];
	t_data		*info;

} t_philo;


//parsin
int		ft_atoi(char *str);
void	ft_error(void);
int		is_num(char *s);
int		parse(int ac, char **av);

#endif