/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:10:36 by vvarussa          #+#    #+#             */
/*   Updated: 2022/04/02 13:36:01 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
    define_fork_indexes(data);
    print_thread_data(*(t_thread_data *)data);
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
}