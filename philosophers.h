/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:44:16 by vvarussa          #+#    #+#             */
/*   Updated: 2022/04/02 13:06:47 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct s_thread_data
{
	pthread_mutex_t *forks_mutexes;
	int             *forks;
	int				right_index;
	int				left_index;
	int             name_of_thread;
	int             number_philo;
	int             time_to_eat;
	int             time_to_die;
	int             time_to_sleep;
	int             number_of_meals;
} t_thread_data;

void			print_thread_data(t_thread_data data);
void			init_forks(int *forks, int size);
t_thread_data	init_thread_data(int argc, char **argv);
t_thread_data	*alloc_thread_data(t_thread_data d, int name);

#endif