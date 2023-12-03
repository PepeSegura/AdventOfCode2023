/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 06:01:07 by psegura-          #+#    #+#             */
/*   Updated: 2023/12/03 07:36:47 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include <fcntl.h>
#include <stdio.h>

void	replace_letters(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			str[i] = str[i];
		else if (str[i] == '.')
			str[i] = str[i];
		else
			str[i] = '*';
		i++;
	}
}

int	get_number(const char *str, int number, int pos)
{
	int	len;
	int	res;
	int	start;

	len = ft_strlen(str);
	res = 0;
	if (pos >= 0 && pos < len)
	{
		start = pos;
		while (start > 0 && str[start - 1] >= '0' && str[start - 1] <= '9')
			start--;
		res = ft_atoi(str + start);
		return (res);
	}
	else
		printf("Invalid pos.\n");
}

#define ROWS 140
#define COLS 140

size_t	locate_numbers(char **matrix)
{
	int		ni;
	int		nj;
	size_t	number;
	int		nb;
	int		prev;
	int		near;
	int		i;
	int		j;

	number = 0;
	nb = 0;
	prev = 0;
	near = 0;
	i = -1;
	while (++i < ROWS)
	{
		j = -1;
		while (++j < COLS)
		{
			if (matrix[i][j] == '*')
			{
				int neighbors[8][2] = {
					{i - 1	, j - 1}, 	{i - 1, j},	{i - 1	, j + 1},
					{i		, j - 1}, 				{i		, j	+ 1},
					{i + 1	, j - 1}, 	{i + 1, j},	{i + 1	, j + 1}
				};

				for (int k = 0; k < 8; k++)
				{
					ni = neighbors[k][0];
					nj = neighbors[k][1];
					if (ni >= 0 && ni < ROWS && nj >= 0 && nj < COLS)
					{
						if (ft_isdigit(matrix[ni][nj]))
						{
							nb = get_number(matrix[ni], matrix[ni][nj], nj);
							if (prev != nb)
							{
								++near;
								if (near >= 2)
									number += nb * prev;
							}
							prev = nb;
						}
					}
				}
				near = 0;
			}
		}
	}
	return (number);
}

int	main(void)
{
	size_t	result;
	int		i;
	int		fd;
	char	**file;

	result = 0;
	i = 0;
	fd = open("file.txt", O_RDWR);
	file = malloc((ROWS + 1) * sizeof(char *));
	while (1)
	{
		file[i] = ft_strtrim(get_next_line(fd), "\n");
		if (!file[i])
			break ;
		replace_letters(file[i]);
		i++;
	}
	result = locate_numbers(file);
	printf("result: [%ld]\n", result);
	close(fd);
}
