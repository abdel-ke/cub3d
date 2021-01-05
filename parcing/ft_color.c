/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:16:26 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/05 16:06:34 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_check_color(t_parcing *p)
{
	if (p->c[0].r == -404 || p->c[0].g == -404 || p->c[0].b == -404 ||
	p->c[0].color == -404)
		return (FALSE);
	if (p->c[1].r == -404 || p->c[1].g == -404 || p->c[1].b == -404 ||
	p->c[1].color == -404)
		return (FALSE);
	return (TRUE);
}

void	check_comma(char *line, int count)
{
	while (*line)
	{
		if (*line == '-')
			ft_error("CHECK COLOR");
		if (*line++ == ',')
			count++;
	}
	if (count != 2)
	{
		free(line);
		ft_error("CHECK COLOR");
	}
}

void	ft_check_atoi(char *line, int i)
{
	char	**check;
	int		start;
	int		end;

	check = ft_split(line, ',');
	while (check[i])
	{
		start = 0;
		while (check[i][start] == ' ')
			start++;
		end = ft_strlen(check[i]) - 1;
		while (check[i][end] == ' ')
			end--;
		while (start <= end)
		{
			if (check[i][start] < '0' || check[i][start] > '9')
			{
				free(check);
				ft_error("error\nCHECK THE COLOR");
			}
			start++;
		}
		i++;
	}
}

void	ft_color(t_parcing *p, char *line, int c_f)
{
	ft_check_atoi(line, 0);
	p->file_args++;
	while (*line == ' ')
		line++;
	p->c[c_f].r = ft_atoi(line);
	while ((*line >= '0' && *line <= '9') || *line == ' ')
		line++;
	if (*line == ',')
		line++;
	p->c[c_f].g = ft_atoi(line);
	while ((*line >= '0' && *line <= '9') || *line == ' ')
		line++;
	if (*line == ',')
		line++;
	p->c[c_f].b = ft_atoi(line);
	if (c_f == C)
		p->c[C].color = p->c[c_f].r * pow(256, 2) +
		p->c[c_f].g * 256 + p->c[c_f].b;
	if (c_f == F)
		p->c[F].color = p->c[c_f].r * pow(256, 2) +
		p->c[c_f].g * 256 + p->c[c_f].b;
}

void	ft_get_color(t_parcing *p, char *line)
{
	check_comma(line, 0);
	if (*line == 'F')
		ft_color(p, line + 1, F);
	if (*line == 'C')
		ft_color(p, line + 1, C);
}
