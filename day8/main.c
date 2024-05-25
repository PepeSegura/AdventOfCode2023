/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 06:01:07 by psegura-          #+#    #+#             */
/*   Updated: 2023/12/10 01:49:53 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

# define SEQUENCE "LRRLRRLRRRLRLLRRRLLRRRLRLRRRLRLRRLRRRLRRRLRLRRRLRRRLRRLRRRLLLRLRRRLRRRLRRRLRLRLRRLLRRRLRLLRLRRRLRRLLRLRLRRLRRRLRRLLRLRRRLLRRLRRRLRLRRLLRRRLRRLLRRLRRRLRLRRRLRRLRRRLRRRLRRLRRRLRLRRLRRRLRRRLRRLLRLRRLRRLRRRLRLLLRRRLLRRRLRLRRRLRLRRLRRRLLLRLRRRLRLRRLRRRLRRRLRRLRLRLRRRR"

void trim_matrix(char **matrix)
{
	int i = 0;
	char *aux;
	
	while (matrix[i])
	{
		aux = matrix[i];
		matrix[i] = ft_strtrim(aux, " \n()");
		free(aux);
		i++;
	}
}

int find_index(char ***game, char *find)
{
	for (int i = 0; game[i][0]; i++)
	{
		if (ft_strcmp(game[i][0], find) == 0)
			return (i);
	}
	return (-1);
}

int steps = 0;

int locate_column(char ***game, int side, int i)
{
	int index = 0;

	steps++;
	// if (side == 1)
	// 	printf("[LEFT] -> [%s]\n", game[i][side]);
	// if (side == 2)
	// 	printf("[RIGHT] -> [%s]\n", game[i][side]);
	index = find_index(game, game[i][side]);
	if (ft_strcmp("ZZZ", game[i][side]) == 0)
	{
		printf("Result: [%d]\n", steps);
		exit(0);	
	}
	return (index);
}

void run_sequence(char ***game)
{
	int i = 0;
	int side = 0;
	int index = 0;
	int len = ft_strlen(SEQUENCE);

	// printf(SEQUENCE"\n");
	while (1)
	{
		if (SEQUENCE[i] == 'L')
			index = locate_column(game, 1, index);
		if (SEQUENCE[i] == 'R')
			index = locate_column(game, 2, index);
		i++;
		if (i == len)
			i = 0;
	}
}

int	main(void)
{
	int		i = 0;
	int		fd = open("file.txt", O_RDWR);
	char	***game = ft_calloc(sizeof(char *),  754 + 1);
	
	
	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break ;
		// printf("Line: %s", line);
		char **move = ft_split(line, '=');
		trim_matrix(move);
		char **move2 = ft_split(move[1], ',');
		trim_matrix(move2);
		char *left = move[0];
		char *right[] = {move2[0],  move2[1]};
		game[i] = ft_calloc(sizeof(char *), 4);
		game[i][0] = left;
		game[i][1] = move2[0];
		game[i][2] = move2[1];
		// printf("%s = (%s, %s)\n", game[i][0],  game[i][1], game[i][2]);
		// printf("Index: [%s] -> Left: [%s] Right: [%s]\n", left,  right[0], right[1]);
		// printf("[%d] Index: [%s] -> Left: [%s] Right: [%s]\n\n", i, game[i][0],  game[i][1], game[i][2]);
		i++;
	}
	run_sequence(game);
	close(fd);
}
