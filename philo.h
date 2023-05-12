/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 01:00:02 by ysahih            #+#    #+#             */
/*   Updated: 2023/05/13 00:12:49 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <stdbool.h>
# include<sys/time.h>
# include<limits.h>

typedef struct s_data
{
	int				nb_philo;
	int				nb_eat;
	unsigned long	to_die;
	unsigned long	to_eat;
	unsigned long	to_sleep;
	unsigned long	start;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_taken;
	unsigned long	last_meal;
	pthread_mutex_t	meal;
	pthread_mutex_t	meals;
	pthread_mutex_t	fork;
	pthread_t		t;
	t_data			*info;
	struct s_philo	*next;
}	t_philo;

//feeding
void			feed_even(t_philo *philo);
void			feed_odd(t_philo *philo);
void			print_status(t_philo *philo );
void			feed_philo(t_philo *philo);

//philospphers
void			*routine(void *arg);
int				create_threads(t_philo *philo);
bool			philos_full(t_philo *philo);
bool			philos_alive(t_philo *philo);

//list utils
void			circular(t_philo *philo);
void			ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo			*ft_lstlast(t_philo *lst);
t_philo			*list_philos(t_data *rules);

//storing up
t_philo			*init_philos(t_data *rules, int id);
int				init_mutex(t_philo *philo);
t_data			*store_up(int ac, char **av);

//parsin
int				ft_atoi(char *str);
void			ft_error(void);
int				is_num(char c);
int				parse(int ac, char **av);

//utils
void			ft_free(t_philo *philo);
void			error_handler(int e);
void			ft_usleep(unsigned long ms, unsigned long now);
void			detach(t_philo *philo);
unsigned long	timeinms(void);

#endif
