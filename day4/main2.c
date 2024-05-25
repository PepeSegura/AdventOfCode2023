/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 06:01:07 by psegura-          #+#    #+#             */
/*   Updated: 2023/12/05 05:05:59 by psegura-         ###   ########.fr       */
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
	int score = 0;
	int i = 0;
	int j = 0;
	while (win[i])
	{
		j = 0;
		while (our[j])
		{
			if (ft_atoi(win[i]) == ft_atoi(our[j]))
			{
				score++;
				break ;
			}
			j++;
		}
		i++;
	}
	// printf("has [%d] matching numbers.\n", score);
	return (score);
}

// Function to calculate the number of copies each card can win
void calculateCopies(char ****cards, int numCards, int *numCopies)
{
    for (int i = numCards - 1; i >= 0; i--)
    {
        int matches = count_score(cards[i][0], cards[i][1]);
		printf("card [%d] has [%d] matching numbers.\n", i + 1, matches);
        numCopies[i] += matches;

        // Each winning card also contributes to the copies of the cards before it
        for (int j = i - 1; j >= 0; j--)
        {
            numCopies[j] += matches;
        }
    }
}

// Function to process a card and its copies
void processCard(char ****cards, int cardIndex, int numCopies, int *totalScore, int *totalCards)
{
    if (numCopies == 0 || cardIndex >= 6) {
        return;  // Stop processing if no copies or if cardIndex is out of bounds
    }

    for (int i = 1; i <= numCopies && (cardIndex + i) < 6; i++)
    {
        int matches = count_score(cards[cardIndex][0], cards[cardIndex + i][1]);
        for (int j = 0; j < matches; j++)
        {
            processCard(cards, cardIndex + i, numCopies * 2, totalScore, totalCards);
        }
    }
    *totalScore += count_score(cards[cardIndex][0], cards[cardIndex][1]);
    *totalCards += numCopies;
}



int	main(void)
{
    int fd;
    int totalScore = 0;
    int totalCards = 0;
    int id = 1;
    int i = 0;

	fd = open("file.txt", O_RDWR);
	char ****file = calloc(sizeof(char ***), (6 + 1));
	while (1)
	{
		file[i] = calloc(sizeof(char **), 3);
		char *line = get_next_line(fd);
		if (!line)
			break ;
		char *start = ft_strchr(line, ':');
		char **aux = ft_split(start + 1, '|');
		free(line);
		trim_matrix(aux);
		file[i][0] = ft_split(aux[0], ' ');
        file[i][1] = ft_split(aux[1], ' ');
		ft_free_matrix(aux);
		// printf("Card: [%d]\n", id);
		// ft_print_matrix(file[i][0], "winning");
		// ft_print_matrix(file[i][1], "our");
		count_score(file[i][0], file[i][1]);
		id++;
		i++;
	}


    // Calculate the number of copies each card can win
	printf("calculate copies\n");
    int *numCopies = calloc(sizeof(int), 6);
    calculateCopies(file, i, numCopies);


    // Process the cards and their copies
	printf("process\n");
    for (int j = 0; j < i -1; j++)
    {
        processCard(file, j, numCopies[j], &totalScore, &totalCards);
    }
    printf("Total score: [%d]\n", totalScore);
    printf("Total cards won: [%d]\n", totalCards);
	close(fd);
}
