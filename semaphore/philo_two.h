/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbudding <sbudding@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:17:15 by sbudding          #+#    #+#             */
/*   Updated: 2021/03/30 17:08:57 by sbudding         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>

typedef struct		s_phil {
	int				ind;
	int				state;
	pthread_t		pthread;
	int				limit;
	int				last_eat;
	struct s_data	*data;
	int				din_cnt;
}					t_phil;

typedef struct		s_data
{
	int				number;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				dinners;
	int				startuem;
	t_phil			*phil;
	sem_t			*sem_lock;
	sem_t			*put_lock;
	sem_t			*deth_lok;
	sem_t			*fork;
	int				frk_cnt;
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
