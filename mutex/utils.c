/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbudding <sbudding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 15:21:43 by sbudding          #+#    #+#             */
/*   Updated: 2021/03/30 17:07:19 by sbudding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			ft_atoi(const char *str)
{
	int				flag;
	unsigned long	num;

	flag = 1;
	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		flag = -1;
	if ((*str == '-') || (*str == '+'))
		str++;
	while ((*str >= '0') && (*str <= '9'))
	{
		num = num * 10 + (*str - '0');
		str++;
		if ((flag > 0) && (num > 9223372036854775807))
			return (-1);
		if ((flag < 0) && (num > 9223372036854775807))
			return (0);
	}
	return (int)(flag * num);
}

void		ft_free(t_data *data)
{
	int		ind;

	ind = 0;
	while (ind < data->number)
	{
		pthread_mutex_destroy(data->fork[ind].fork_mut);
		free(data->fork[ind].fork_mut);
		pthread_mutex_destroy(data->phil[ind].check);
		free(data->phil[ind].check);
		ind++;
	}
	pthread_mutex_destroy(data->put_lock);
	free(data->put_lock);
	pthread_mutex_destroy(data->deth_lok);
	free(data->deth_lok);
	free(data->fork);
	free(data->phil);
	free(data);
}

int			ft_time_now(void)
{
	struct timeval	tv;
	int				time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void		ft_put(char *str, t_phil *fil)
{
	int		s;
	int		ms;

	s = (ft_time_now() - fil->data->startuem) / 1000;
	ms = (ft_time_now() - fil->data->startuem) % 1000;
	pthread_mutex_lock(fil->data->put_lock);
	printf("%d.%03d %d %s\n", s, ms, fil->ind + 1, str);
	str[0] != 'd' ? pthread_mutex_unlock(fil->data->put_lock) : 0;
}

void		ft_dinners(t_data *data)
{
	int		ind;

	while (2007)
	{
		ind = 0;
		while (ind < data->number)
		{
			if (data->phil[ind].din_cnt != data->dinners)
				ind = data->number;
			ind++;
		}
		if (ind == data->number || data->rip)
		{
			pthread_mutex_unlock(data->deth_lok);
			return ;
		}
	}
}
