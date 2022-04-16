/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:10:36 by vvarussa          #+#    #+#             */
/*   Updated: 2022/04/15 23:16:39 by vvarussa         ###   ########.fr       */
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

    sem_wait(data.print);
	gettimeofday(&data.end, NULL);
	timestamp = get_interval_time(data.end, data.begin);
	printf("%-5ld %d %s\n", timestamp, data.name_of_thread, message);
    sem_post(data.print);
}

int     has_died(t_thread_data *data)
{
    long timestamp;

    gettimeofday(&data->end, NULL);
    timestamp = get_interval_time(data->end, data->thinking_time);
    if (timestamp > data->time_to_die)
        return (1);
    return (0);
}

void    child_process(t_thread_data data)
{
    sem_t *t;
    t = sem_open("print", O_CREAT, 0777, 1);

    sem_wait(t);
    // print_thread_data(data);
    printf("b\n");
    sem_post(t);
    exit(0);
}

// void    parent_process(t_thread_data data)
// {
//     printf("MAIN\n");
//     exit(2);
// }

void    run_processes(t_thread_data data)
{
    int n;
    int pid;

    n = data.number_philo;
    while (n > 0)
    {
        pid = fork();
        if (pid == 0)
        {
            data.name_of_thread = n;
            child_process(data);
        }
        n--;
    }
    // while(wait(NULL) > 0);
}

int main(int argc, char **argv)
{
    t_thread_data data;

    data = init_thread_data(argc, argv);
    run_processes(data);
}
