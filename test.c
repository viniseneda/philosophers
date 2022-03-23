/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:10:36 by vvarussa          #+#    #+#             */
/*   Updated: 2022/03/23 14:39:56 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

int c = 0;
int size = 5;

typedef struct s_forks
{
    pthread_mutex_t **forks;
    int             name_of_thread;
    int             number_philo;
    int             time_to_eat;
    int             time_to_die;
    int             time_to_sleep;
    int             numeber_of_meals;
} t_forks;

// use a single thread for all the info. Test using malloc to allocate heap space, and them "copying" a previous template with "="

void *thread(void *mut)
{
    pthread_mutex_lock(mut);
    c++;
    printf("%d\n", c);
    pthread_mutex_unlock(mut);
    return (NULL);
}

int main(int argc, char **argv)
{
    int n = size;
    pthread_mutex_t mut[size];

    n = size;
    while (n > 0)
    {
        n--;
        pthread_mutex_init(&mut[n], NULL);
    }
    
    pthread_t test[n];

    while (n > 0)
    {
        n--;
        if(pthread_create(&test[n], NULL, &thread, &mut) != 0)
            perror("failed to create thread");
    }
    
    n = size;
    while (n > 0)
    {
        n--;
        if(pthread_join(test[n], NULL) != 0)
            perror("failed to create thread");
    }
}