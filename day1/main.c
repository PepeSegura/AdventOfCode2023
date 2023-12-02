/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:20:04 by psegura-          #+#    #+#             */
/*   Updated: 2023/12/02 14:10:26 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include <fcntl.h>
#include <stdio.h>

char *numbers[] = {
	"zero",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	NULL
};

int locate_number(char *str)
{
	int i = 0;

	while (numbers[i])
	{
		if (ft_strnstr(str, numbers[i], ft_strlen(numbers[i])))
			return (i);
		i++;
	}
	return (-1);
}

int first(char *str)
{
	int i = 0;
	int number = 0;

	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (str[i] - 48);
		if ((number = locate_number(str + i)) != -1)
			return (number);
		i++;
	}
	return (0);
}

int last(char *str)
{
	int i = ft_strlen(str) - 1;
	int number = 0;

	while (i >= 0)
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (str[i] - 48);
		if ((number = locate_number(str + i)) != -1)
			return (number);
		i--;
	}
	return (0);
}

int main(void)
{
	char *line = NULL;
	int fd = open("file.txt", O_RDWR);
	int result = 0;

	int first_nb = 0;
	int last_nb = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		first_nb = first(line) * 10;
		last_nb = last(line);
		result = result + (first_nb + last_nb);
		free(line);
	}
	printf("RES: %d\n", result);
}
