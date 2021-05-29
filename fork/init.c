/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbudding <sbudding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:31:47 by sbudding          #+#    #+#             */
/*   Updated: 2021/03/30 17:10:23 by sbudding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
		phil[ind].data = data;
		phil[ind].din_cnt = 0;
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
	data->frk_cnt = ft_atoi(argv[1]);
	data->rip = 0;
	return (0);
}

t_data		*ft_init_data(char **argv)
{
	t_data		*data;
	int			ind;

	data = malloc(sizeof(t_data));
	ft_parse(data, argv);
	ind = 0;
	sem_unlink("fork");
	data->fork = sem_open("fork", O_CREAT | O_EXCL, 0777, data->number);
	sem_unlink("sem_lock");
	data->sem_lock = sem_open("sem_lock", O_CREAT | O_EXCL, 0777, 1);
	sem_unlink("put_lock");
	data->put_lock = sem_open("put_lock", O_CREAT | O_EXCL, 0777, 1);
	sem_unlink("deth_lok");
	data->deth_lok = sem_open("deth_lok", O_CREAT | O_EXCL, 0777, 1);
	sem_wait(data->deth_lok);
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
