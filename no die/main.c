/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:10:36 by vvarussa          #+#    #+#             */
/*   Updated: 2022/04/13 10:08:28 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long    get_interval_time(struct timeval end, struct timeval begin)
{
    return ((end.tv_sec * 1000000 + end.tv_usec) / 1000) -
        ((begin.tv_sec * 1000000 + begin.tv_usec) / 1000);
}

void	print_message(char *message, t_thread_data data)
{
	long timestamp;

	gettimeofday(&data.end, NULL);
	timestamp = get_interval_time(data.end, data.begin);
	pthread_mutex_lock(&data.forks_mutexes[data.number_philo]);
	printf("%ld %d %s\n", timestamp, data.name_of_thread, message);
	pthread_mutex_unlock(&data.forks_mutexes[data.number_philo]);
}

void	print_data_mute(t_thread_data data)
{
	//long timestamp;

	gettimeofday(&data.end, NULL);
	//timestamp =
	pthread_mutex_lock(&data.forks_mutexes[data.number_philo]);
	print_thread_data(data);
	pthread_mutex_unlock(&data.forks_mutexes[data.number_philo]);
}

void    define_fork_indexes(t_thread_data *data)
{
    if (data->name_of_thread - 2 < 0)
        data->left_index = data->number_philo - 1;
    else
        data->left_index = data->name_of_thread - 2;

    data->right_index = data->name_of_thread - 1;
}

// void *thread(void *data)
// {
//     define_fork_indexes(data);
//     // print_thread_data(*(t_thread_data *)data);
// 	print_data_mute(*(t_thread_data *)data);
//     free(data);
//     return (NULL);
// }

int	try_to_eat(t_thread_data *data)
{
	if (data->name_of_thread % 2 == 1)
		usleep(10000);
	if (data->forks[data->left_index] && data->forks[data->right_index])
	{
		// printf("A\n");
		pthread_mutex_lock(&data->forks_mutexes[data->left_index]);
		data->forks[data->left_index] = 0;
		pthread_mutex_lock(&data->forks_mutexes[data->right_index]);
		data->forks[data->right_index] = 0;

		print_message("eating", *data);
		usleep(data->time_to_eat);

		data->forks[data->left_index] = 1;
		pthread_mutex_unlock(&data->forks_mutexes[data->left_index]);
		data->forks[data->left_index] = 1;
		pthread_mutex_unlock(&data->forks_mutexes[data->left_index]);
		return (1);
	}
	return (0);
}

int	try_to_eat_2(t_thread_data *data)
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
			// print_message("has taken a fork", *data);
			data->forks[data->right_index] = 0;
			pthread_mutex_unlock(&data->forks_mutexes[data->right_index]);
			print_message("is eating", *data);
			usleep(data->time_to_eat);
			print_message("is sleeping", *data);
			usleep(data->time_to_sleep);
			pthread_mutex_lock(&data->forks_mutexes[data->left_index]);
			data->forks[data->left_index] = 1;
			pthread_mutex_unlock(&data->forks_mutexes[data->left_index]);
			pthread_mutex_lock(&data->forks_mutexes[data->right_index]);
			data->forks[data->right_index] = 1;
			pthread_mutex_unlock(&data->forks_mutexes[data->right_index]);
			return(1);
		}
		pthread_mutex_unlock(&data->forks_mutexes[data->right_index]);
		pthread_mutex_lock(&data->forks_mutexes[data->left_index]);
		data->forks[data->left_index] = 1;
		pthread_mutex_unlock(&data->forks_mutexes[data->left_index]);
		return (0);
	}
	pthread_mutex_unlock(&data->forks_mutexes[data->left_index]);
	return (0);
}

void *thread(void *data)
{
    t_thread_data *d;
	// long timestamp;

    d = (t_thread_data *)data;
    define_fork_indexes(data);
	gettimeofday(&d->begin, NULL);
    while (d->number_of_meals != 0)
    {
        gettimeofday(&d->thinking_time, NULL);
		// printf("%d\n", d->forks[d->left_index]);
		print_message("is thinking", *d);
        while(!try_to_eat_2(d))
		{
			// gettimeofday(&d->end, NULL);
			// timestamp = get_interval_time(d->end, d->thinking_time);
			// // printf("(%ld, %d)\n", timestamp, d->time_to_die);
			// if (timestamp > d->time_to_die)
			// {
			// 	print_message("died", *d);
			// 	d->forks[d->number_philo] = 1;
			// }
		}
        d->number_of_meals = d->number_of_meals - 1;
    }
    free(data);
    return (NULL);
}

void    run_threads(t_thread_data data)
{
    pthread_mutex_t mutexes[data.number_philo + 1];
    pthread_t       philosophers[data.number_philo];
    int n;

    n = data.number_philo + 1;
    while (n > 0)
    {
        n--;
        pthread_mutex_init(&mutexes[n], NULL);
    }
    data.forks_mutexes = mutexes;
    n = data.number_philo;
    while (n > 0)
    {
        n--;
        if(pthread_create(&philosophers[n], NULL, &thread, alloc_thread_data(data, n + 1)) != 0)
            perror("failed to create thread");
    }
    n = data.number_philo;
    while (n > 0)
    {
        n--;
        if(pthread_join(philosophers[n], NULL) != 0)
            perror("failed to create thread");
    }
}

int main(int argc, char **argv)
{
    t_thread_data data;

    data = init_thread_data(argc, argv);
    run_threads(data);
	free(data.forks);
}
