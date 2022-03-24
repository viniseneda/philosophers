/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:10:36 by vvarussa          #+#    #+#             */
/*   Updated: 2022/03/24 14:39:13 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int c = 0;

typedef struct s_thread_data
{
    pthread_mutex_t *forks;
    int             name_of_thread;
    int             number_philo;
    int             time_to_eat;
    int             time_to_die;
    int             time_to_sleep;
    int             number_of_meals;
} t_thread_data;

// use a single thread for all the info. Test using malloc to allocate heap space, and them "copying" a previous template with "="

void    print_thread_data(t_thread_data data)
{
    printf("name: %d\n", data.name_of_thread);
    printf("number of philosophers: %d\n", data.number_philo);
    printf("time to die: %d\n", data.time_to_die);
    printf("time to eat: %d\n", data.time_to_eat);
    printf("time to sleep: %d\n", data.time_to_sleep);
    printf("number of meals: %d\n", data.number_of_meals);
    printf("\n");
}

void *thread(void *data)
{
    print_thread_data(*(t_thread_data *)data);
    free(data);
    return (NULL);
}


t_thread_data init_thread_data(int argc, char **argv)
{
    t_thread_data data;

    if (argc < 5 || argc > 6)
    {
        printf("wrong number of arguments\n");
        exit(3);
    } 
    data.name_of_thread = 0;
    data.number_philo = atoi(argv[1]);
    data.time_to_die = atoi(argv[2]);
    data.time_to_eat = atoi(argv[3]);
    data.time_to_sleep = atoi(argv[4]);
    if (argc == 5)
        data.number_of_meals = -1;
    else
        data.number_of_meals = atoi(argv[5]);
    return (data);
}

t_thread_data *alloc_thread_data(t_thread_data d, int name)
{
    t_thread_data *data;

    data = (t_thread_data *) malloc(sizeof(t_thread_data));
    *data = d;
    data->name_of_thread = name;
    return (data);
}

void    run_threads(t_thread_data data)
{
    pthread_mutex_t mutexes[data.number_philo];
    pthread_t philosophers[data.number_philo];
    int n;

    n = data.number_philo;
    while (n > 0)
    {
        n--;
        pthread_mutex_init(&mutexes[n], NULL);
    }
    data.forks = mutexes;
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
    // print_thread_data(*(alloc_thread_data(data, 1)));
    // pthread_t test[n];

    // while (n > 0)
    // {
    //     n--;
    //     if(pthread_create(&test[n], NULL, &thread, &mut) != 0)
    //         perror("failed to create thread");
    // }
    
    // n = size;
    // while (n > 0)
    // {
    //     n--;
    //     if(pthread_join(test[n], NULL) != 0)
    //         perror("failed to create thread");
    // }
}