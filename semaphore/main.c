/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbudding <sbudding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:23:48 by sbudding          #+#    #+#             */
/*   Updated: 2021/03/30 17:02:41 by sbudding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*ft_check_death(t_phil *fil)
{
	while (42)
	{
		usleep(100);
		if (fil->data->rip || fil->din_cnt == fil->data->dinners)
			return (NULL);
		if (fil->state != 2 && (ft_time_now() > fil->limit))
		{
			fil->state = 0;
			fil->data->rip = 1;
			ft_put("died", fil);
			sem_post(fil->data->deth_lok);
			return (NULL);
		}
	}
}

void	ft_eat(t_phil *fil)
{
	sem_wait(fil->data->sem_lock);
	fil->data->frk_cnt -= 2;
	sem_wait(fil->data->fork);
	ft_put("has taken fork", fil);
	sem_wait(fil->data->fork);
	ft_put("has taken fork", fil);
	sem_post(fil->data->sem_lock);
	fil->state = 2;
	fil->last_eat = ft_time_now();
	fil->limit = fil->last_eat + fil->data->t_die;
	ft_put("is eating", fil);
	usleep(fil->data->t_eat * 1000);
	sem_post(fil->data->fork);
	sem_post(fil->data->fork);
	fil->data->frk_cnt += 2;
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
		if (fil->data->frk_cnt > 1)
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
		pthread_create(&data->phil[i].pthread, NULL, ft_being, &data->phil[i]);
		i++;
	}
	(data->dinners != -1) ? ft_dinners(data) : 0;
	sem_wait(data->deth_lok);
	ft_free(data);
	return (0);
}
