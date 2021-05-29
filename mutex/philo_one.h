/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbudding <sbudding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:17:15 by sbudding          #+#    #+#             */
/*   Updated: 2021/03/30 17:28:17 by sbudding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct		s_forks
{
	pthread_mutex_t	*fork_mut;
	int				ind;
}					t_forks;

typedef struct		s_phil {
	int				ind;
	int				state;
	pthread_t		pthread;
	int				limit;
	int				last_eat;
	t_forks			*r_fork;
	t_forks			*l_fork;
	struct s_data	*data;
	int				din_cnt;
	pthread_mutex_t	*check;
}					t_phil;

typedef struct		s_data
{
	int				number;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				dinners;
	int				startuem;
	t_forks			*fork;
	pthread_mutex_t	*put_lock;
	pthread_mutex_t	*deth_lok;
	t_phil			*phil;
	int				rip;
}					t_data;

void				ft_free(t_data *data);
void				ft_put(char *str, t_phil *fil);
int					ft_atoi(const char *str);
void				ft_put(char *str, t_phil *fil);
int					ft_time_now(void);

void				ft_invalid(int argc, char **argv);
int					ft_parse(t_data *data, char **argv);
t_phil				*ft_init_phils(t_data *data);
t_data				*ft_init_data(char **argv);
void				ft_dinners(t_data *data);

#endif
