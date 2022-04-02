/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:50:12 by vvarussa          #+#    #+#             */
/*   Updated: 2022/04/02 13:12:11 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_forks(int *forks, int size)
{
    while (size > 0)
    {
        printf("%d, ", forks[size - 1]);
        size--;
    }
    printf("\n");
}

void    print_thread_data(t_thread_data data)
{
    int n;

    n = data.number_philo;
    printf("name: %d\n", data.name_of_thread);
    printf("number of philosophers: %d\n", data.number_philo);
    printf("time to die: %d\n", data.time_to_die);
    printf("right fork index: %d\n", data.right_index);
    printf("left fork index: %d\n", data.left_index);
    // print_forks(data.forks, data.number_philo);
    printf("time to eat: %d\n", data.time_to_eat);
    printf("time to sleep: %d\n", data.time_to_sleep);
    printf("number of meals: %d\n", data.number_of_meals);
    printf("\n");
}

void    init_forks(int *forks, int size)
{
    while (size > 0)
    {
        forks[size - 1] = 1;
        size--;
    }
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
    data.forks = (int *) malloc(data.number_philo * sizeof(int));
    init_forks(data.forks, data.number_philo);
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