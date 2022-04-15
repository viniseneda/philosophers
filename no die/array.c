/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:52:45 by vvarussa          #+#    #+#             */
/*   Updated: 2022/03/24 13:49:31 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void    print_array(int *array)
{
    int i = 0;
    while (i < 4)
    {
        printf("%d, ", array[i]);
        i++;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int a[5] = {1, 2, 4, 5, 6};
    // int *a;
    
    // mall
    print_array(a);
}
