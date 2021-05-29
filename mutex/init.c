/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbudding <sbudding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:31:47 by sbudding          #+#    #+#             */
/*   Updated: 2021/03/30 17:28:17 by sbudding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_phil		*ft_init_phils(t_data *data)
{
	t_phil	*phil;
	int		ind;

	phil = malloc(data->number * sizeof(t_phil));
	ind = 0;
	while (ind < data->number)
	{
		phil[ind].limit = 0;
		phil[ind].state = 1;
		phil[ind].ind = ind;
		phil[ind].r_fork = &data->fork[ind];
		phil[ind].l_fork = &data->fork[(ind + 1) % data->number];
		phil[ind].data = data;
		phil[ind].din_cnt = 0;
		phil[ind].check = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(phil[ind].check, NULL);
		ind++;
	}
	return (phil);
}

int			ft_parse(t_data *data, char **argv)
{
	data->number = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->dinners = (argv[5]) ? ft_atoi(argv[5]) : -1;
	data->startuem = ft_time_now();
	data->rip = 0;
	return (0);
}

t_data		*ft_init_data(char **argv)
{
	t_data		*data;
	int			ind;

	data = malloc(sizeof(t_data));
	ft_parse(data, argv);
	data->fork = malloc(data->number * sizeof(t_forks));
	ind = 0;
	while (ind < data->number)
	{
		data->fork[ind].fork_mut = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(data->fork[ind].fork_mut, NULL);
		data->fork[ind].ind = -1;
		ind++;
	}
	data->put_lock = malloc(sizeof(pthread_mutex_t));
	data->deth_lok = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->put_lock, NULL);
	pthread_mutex_init(data->deth_lok, NULL);
	pthread_mutex_lock(data->deth_lok);
	return (data);
}

void		ft_invalid(int argc, char **argv)
{
	if (argc > 6 ||
		argc < 5 ||
		ft_atoi(argv[1]) < 2 ||
		ft_atoi(argv[1]) > 200 ||
		ft_atoi(argv[2]) < 60 ||
		ft_atoi(argv[3]) < 60 ||
		ft_atoi(argv[4]) < 60 ||
		(argv[5] && ft_atoi(argv[5]) < 0))
	{
		write(1, "Invalid arguments. RTFM\n", 24);
		exit(-1);
	}
}
