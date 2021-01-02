/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 17:16:09 by abdel-ke          #+#    #+#             */
/*   Updated: 2020/12/17 18:12:10 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.c"
#include "get_next_line_utils.c"
// #include "../cube.h"

void ft_putchar(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void stock_resol(char *line, int w, int h)
{
	// printf("|%s|\t|%c|\n", line, *line);
	// puts("ok");
	while (*line == ' ')
		line++;
	w = atoi(line);
	while ((*line >= '0' && *line <= '9') || *line == ' ')
		line++;
	printf("[%c]\n", *line);
	h = atoi(line);
	while ((*line >= '0' && *line <= '9') || *line == ' ')
		line++;
	h = h > 1440 ? 1440 : h;
	w = w > 2560 ? 2560 : w;
		printf("%d\t%d\n", w, h);
		//puts("ok");
}

void check_get(char *l_1, int w, int h)
{
	int i = 0;
	while (*l_1 != '\n')
	{
		if (l_1[0] == 'R' && l_1[1] == ' ')
			stock_resol(++l_1, w, h);
		l_1++;
	}
}

void ft_parse(int ac, char **av)
{
	int fd;
	char *line;

	if (ac < 1 || ac > 3 || (fd = open(av[1], O_RDONLY) == -1)
		ft_putchar("error in arguments :p\n");
	check_get(&line, fd);
}

int main(int ac, char **av)
{
	int fd = open("cub.cub", O_RDONLY);
	char *line, *l_1;
	// int c = -1;
	int w, h;
	while (get_next_line(fd, &line))
	{
		// c = get_next_line(fd, &line);
		// get_next_line(fd, &line);
		check_get(line, w, h);
		// printf("%d\t%s\n", c, line);
	}
	return (0);
}
