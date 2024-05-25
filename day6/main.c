/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:31:56 by psegura-          #+#    #+#             */
/*   Updated: 2023/12/06 21:19:01 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

int calc_wins(int max_race_time, int min_distance_to_win)
{
    int wins = 0;
    int distance = 0;

    for (int speed = 0; speed <= max_race_time; speed++)
    {
        distance = speed * (max_race_time - speed);
        if (distance > min_distance_to_win)
            wins++;
    }
    return (wins);
}

int main(void)
{
    int result = calc_wins(15, 40);
    printf("result: [%d]\n", result);
}

            // printf("max_race_time: %f Distance: %f Speed: %f Rival: %f\n", time, distance, speed, rival);
// 49678386
// 7139945
