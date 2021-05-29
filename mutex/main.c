/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbudding <sbudding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:23:48 by sbudding          #+#    #+#             */
/*   Updated: 2021/03/30 17:28:17 by sbudding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_check_death(t_phil *fil)
{
	while (42)
	{
		usleep(100);
		if (fil->data->rip || fil->din_cnt == fil->data->dinners)
			return (NULL);
		pthread_mutex_lock(fil->check);
		if (fil->state != 2 && (ft_time_now() > fil->limit))
		{
			fil->state = 0;
			fil->data->rip = 1;
			ft_put("died", fil);
			pthread_mutex_unlock(fil->data->deth_lok);
			pthread_mutex_unlock(fil->check);
			return (NULL);
		}
		pthread_mutex_unlock(fil->check);
	}
}

void	ft_eat(t_phil *fil)
{
	if (fil->ind % 2)
	{
		pthread_mutex_lock(fil->l_fork->fork_mut);
		fil->l_fork->ind = fil->ind;
		ft_put("has taken a fork", fil);
	}
	pthread_mutex_lock(fil->r_fork->fork_mut);
	fil->r_fork->ind = fil->ind;
	ft_put("has taken a fork", fil);
	if (!(fil->ind % 2))
	{
		pthread_mutex_lock(fil->l_fork->fork_mut);
		fil->l_fork->ind = fil->ind;
		ft_put("has taken a fork", fil);
	}
	pthread_mutex_lock(fil->check);
	fil->state = 2;
	fil->last_eat = ft_time_now();
	fil->limit = fil->last_eat + fil->data->t_die;
	pthread_mutex_unlock(fil->check);
	ft_put("is eating", fil);
	usleep(fil->data->t_eat * 1000);
	pthread_mutex_unlock(fil->r_fork->fork_mut);
	pthread_mutex_unlock(fil->l_fork->fork_mut);
	fil->din_cnt++;
}

void	ft_being_2(t_phil *fil)
{
	if (fil->state && !fil->data->rip)
	{
		fil->state = 3;
		ft_put("is sleeping", fil);
		usleep(fil->data->t_sleep * 1000);
	}
	if (fil->state && !fil->data->rip)
	{
		fil->state = 1;
		ft_put("is thinking", fil);
	}
}

void	*ft_being(void *argv)
{
	pthread_t		check_death;
	t_phil			*fil;

	fil = (t_phil*)argv;
	pthread_detach(fil->pthread);
	fil->last_eat = ft_time_now();
	fil->limit = fil->last_eat + fil->data->t_die;
	pthread_create(&check_death, NULL, (void*)&ft_check_death, fil);
	pthread_detach(check_death);
	while (fil->state && !fil->data->rip && fil->din_cnt != fil->data->dinners)
	{
		if (fil->l_fork->ind != fil->ind && fil->r_fork->ind != fil->ind)
			ft_eat(fil);
		else
			continue;
		ft_being_2(fil);
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	t_data		*data;
	int			i;

	ft_invalid(argc, argv);
	data = ft_init_data(argv);
	data->phil = ft_init_phils(data);
	i = 0;
	while (i < data->number)
	{
		usleep(50);
		pthread_create(&data->phil[i].pthread, NULL, ft_being, &data->phil[i]);
		i++;
	}
	(data->dinners != -1) ? ft_dinners(data) : 0;
	pthread_mutex_lock(data->deth_lok);
	ft_free(data);
	return (0);
}
