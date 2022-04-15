/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 09:45:11 by vvarussa          #+#    #+#             */
/*   Updated: 2022/04/01 10:27:20 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    struct timeval	begin;
    struct timeval	end;
	long			time;

    gettimeofday(&begin, NULL);
	// usleep(500);
	sleep(1);
    gettimeofday(&end, NULL);
	time = (end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec);
	printf("%ld\n", time);
	
    
}