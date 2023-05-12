/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahih <ysahih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 00:52:32 by ysahih            #+#    #+#             */
/*   Updated: 2023/05/13 00:48:42 by ysahih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*ft_lstlast(t_philo *lst){
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*last_node;

	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}

void	circular(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = philo;
}

t_philo	*list_philos(t_data *rules)
{
	t_philo	*philo;
	t_philo	*node;
	int		i;

	i = 0;
	philo = NULL;
	while (i < rules->nb_philo)
	{
		node = init_philos(rules, i);
		if (!node)
			return (NULL);
		ft_lstadd_back(&philo, node);
		i++;
	}
	circular(philo);
	return (philo);
}
