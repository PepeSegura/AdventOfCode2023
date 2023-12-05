/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 06:01:07 by psegura-          #+#    #+#             */
/*   Updated: 2023/12/05 03:40:22 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

void trim_matrix(char **matrix)
{
	int i = 0;
	char *aux;
	
	while (matrix[i])
	{
		aux = matrix[i];
		matrix[i] = ft_strtrim(aux, " \n");
		free(aux);
		i++;
	}
}
int	count_score(char **win, char **our)
{
	int score = 1;
	int i = 0;
	int j = 0;
	while (win[i])
	{
		j = 0;
		while (our[j])
		{
			if (ft_atoi(win[i]) == ft_atoi(our[j]))
				score = score << 1;
			j++;
		}
		i++;
	}
	return (score >> 1);
}

int	main(void)
{
	int	fd;
	int	result = 0;

	fd = open("file.txt", O_RDWR);
	while (1)
	{
		
		char *line = get_next_line(fd);
		if (!line)
			break ;
		char *start = ft_strchr(line, ':');

		char **game = ft_split(start + 1, '|');
		trim_matrix(game);
		
		ft_print_matrix(game, "game");
		char **winning = ft_split(game[0], ' ');
		ft_print_matrix(winning, "winning");
		char **our = ft_split(game[1], ' ');
		ft_print_matrix(our, "our");

		result += count_score(winning, our);
	}
	printf("result: [%d]\n", result);
	close(fd);
}
