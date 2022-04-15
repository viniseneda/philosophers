/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_to_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:44:56 by vvarussa          #+#    #+#             */
/*   Updated: 2022/04/15 12:07:03 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_fork(t_thread_data *data, int fork_index, int value)
{
	pthread_mutex_lock(&data->forks_mutexes[fork_index]);
	data->forks[fork_index] = value;
	pthread_mutex_unlock(&data->forks_mutexes[fork_index]);
}

int	try_to_eat(t_thread_data *data)
{
	// if (data->name_of_thread % 2 == 1)
	// 	usleep(10000);
	pthread_mutex_lock(&data->forks_mutexes[data->left_index]);
	if (data->forks[data->left_index])
	{
		// print_message("has taken a fork", *data);
		data->forks[data->left_index] = 0;
		pthread_mutex_unlock(&data->forks_mutexes[data->left_index]);
		pthread_mutex_lock(&data->forks_mutexes[data->right_index]);
		if (data->forks[data->right_index])
		{
			print_message("has taken a fork", *data);
			print_message("has taken a fork", *data);
			data->forks[data->right_index] = 0;
			pthread_mutex_unlock(&data->forks_mutexes[data->right_index]);
			print_message("is eating", *data);


			gettimeofday(&data->thinking_time, NULL);
			usleep(data->time_to_eat);

			// pthread_mutex_lock(&data->forks_mutexes[data->left_index]);
			// data->forks[data->left_index] = 1;
			// pthread_mutex_unlock(&data->forks_mutexes[data->left_index]);
			set_fork(data, data->left_index, 1);

			// pthread_mutex_lock(&data->forks_mutexes[data->right_index]);
			// data->forks[data->right_index] = 1;
			// pthread_mutex_unlock(&data->forks_mutexes[data->right_index]);
			set_fork(data, data->right_index, 1);

			print_message("is sleeping", *data);
			usleep(data->time_to_sleep);
			return(1);
		}
		pthread_mutex_unlock(&data->forks_mutexes[data->right_index]);

		// pthread_mutex_lock(&data->forks_mutexes[data->left_index]);
		// data->forks[data->left_index] = 1;
		// pthread_mutex_unlock(&data->forks_mutexes[data->left_index]);
		set_fork(data, data->left_index, 1);
		return (0);
	}
	pthread_mutex_unlock(&data->forks_mutexes[data->left_index]);
	// gettimeofday(&data->thinking_time, NULL);
	return (0);
}
