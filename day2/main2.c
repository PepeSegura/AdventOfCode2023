/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:44:07 by psegura-          #+#    #+#             */
/*   Updated: 2023/12/02 14:03:16 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include <fcntl.h>
#include <stdio.h>

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

int find_color(char **input, char *color)
{
	int i = -1;

	while (input[++i])
	{
		if (ft_strnstr(input[i], color, ft_strlen(input[i])))
			return (ft_atoi(input[i]));
	}
	return (0);
}

int	locate_data(char **matrix)
{
	int i = 0;

	int red = 0;
	int green = 0;
	int blue = 0;

	int m_red = 0;
	int m_green = 0;
	int m_blue = 0;

	while (matrix[i])
	{
		char **out = ft_split(matrix[i], ',');
		trim_matrix(out);
		if ((red = find_color(out, "red")) > m_red)
			m_red = red;
		if ((green = find_color(out, "green")) > m_green)
			m_green = green;
		if ((blue = find_color(out, "blue")) > m_blue)
			m_blue = blue;
		ft_free_matrix(out);
		i++;
	}
	return (m_red * m_green * m_blue);
}

int main(void)
{
	int	game_id = 1;
	int result = 0;
	int power = 0;
	int fd = open("file.txt", O_RDWR);

	char *line;
	char **semicolon;
	char *start;

	while (1)
	{	
		line = get_next_line(fd);
		if (!line)
			break ;
		start = ft_strchr(line, ':');
		semicolon = ft_split(start + 1, ';');
		trim_matrix(semicolon);
		if ((power = locate_data(semicolon)) != -1)
			result = result + power;
		free(line);
		ft_free_matrix(semicolon);
		game_id++;
	}
	printf("result: [%d]\n", result);
	close(fd);
}
