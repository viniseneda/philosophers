/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:44:16 by vvarussa          #+#    #+#             */
/*   Updated: 2022/04/15 23:05:38 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>

typedef struct s_thread_data
{
	sem_t			*print;
	sem_t			*forks;
	sem_t			*kill;
	struct timeval	begin;
	struct timeval	thinking_time;
    struct timeval	end;
	int             name_of_thread;
	int             number_philo;
	int             time_to_eat;
	int             time_to_die;
	int             time_to_sleep;
	int             number_of_meals;
} t_thread_data;

void			print_thread_data(t_thread_data data);
t_thread_data	init_thread_data(int argc, char **argv);
int				try_to_eat(t_thread_data *data);
void			print_message(char *message, t_thread_data data);
int				has_died(t_thread_data *data);
void			die(t_thread_data *data);

#endif
