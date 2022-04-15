/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:10:36 by vvarussa          #+#    #+#             */
/*   Updated: 2022/04/15 19:05:08 by vvarussa         ###   ########.fr       */
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
	printf("%-5ld %d %s\n", timestamp, data.name_of_thread, message);
	pthread_mutex_unlock(&data.forks_mutexes[data.number_philo]);
}

void	print_data_mute(t_thread_data data)
{
	gettimeofday(&data.end, NULL);
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

void *thread(void *data)
{
    t_thread_data *d;
	long timestamp;

    d = (t_thread_data *)data;
    define_fork_indexes(data);
	gettimeofday(&d->begin, NULL);
	gettimeofday(&d->thinking_time, NULL);
    while (d->number_of_meals != 0 && !has_died(data))
    {
		print_message("is thinking", *d);
        while(!try_to_eat(d) && !has_died(data))
		{
			gettimeofday(&d->end, NULL);
			timestamp = get_interval_time(d->end, d->thinking_time);
			if (timestamp > d->time_to_die)
			{
				// print_message("died", *d);
				// printf("(%d, %ld, %d)\n", d->name_of_thread, timestamp, d->time_to_die);
				// d->forks[d->number_philo] = 1;
                die(data);
			}
		}
        d->number_of_meals = d->number_of_meals - 1;
    }
    free(data);
    return (NULL);
}

void    init_mutexes(t_thread_data *data, pthread_mutex_t *m)
{
    int n;

    n = data->number_philo + 2;
    while (n > 0)
    {
        n--;
        pthread_mutex_init(&m[n], NULL);
    }
    data->forks_mutexes = m;
}

void    run(pthread_t *philosophers, t_thread_data *data)
{
    int n;

    n = data->number_philo;
    while (n > 0)
    {
        n--;
        if(pthread_create(&philosophers[n], NULL, &thread, alloc_thread_data(*data, n + 1)) != 0)
            perror("failed to create thread");
    }
}

void    run_threads(t_thread_data data)
{
    pthread_mutex_t mutexes[data.number_philo + 2];
    pthread_t       philosophers[data.number_philo];
    int n;

    // n = data.number_philo + 2;
    // while (n > 0)
    // {
    //     n--;
    //     pthread_mutex_init(&mutexes[n], NULL);
    // }
    // data.forks_mutexes = mutexes;
    init_mutexes(&data, mutexes);

    // n = data.number_philo;
    // while (n > 0)
    // {
    //     n--;
    //     if(pthread_create(&philosophers[n], NULL, &thread, alloc_thread_data(data, n + 1)) != 0)
    //         perror("failed to create thread");
    // }
    run(philosophers, &data);

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
