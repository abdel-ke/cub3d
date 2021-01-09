/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcing_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 11:46:33 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/09 17:22:55 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_check_line(char *line)
{
	if (line[0] != '1' || line[ft_strlen(line) - 1] != '1' ||
		line[0] != ' ' || line[ft_strlen(line) - 1] != ' ')
		return (FALSE);
	return (TRUE);
}

void	map_out_up_down(t_parcing *p, int pos)
{
	int start;
	int end;

	start = 0;
	end = p->map.nbr_cols - 1;
	while (p->map.map[pos][start] == ' ')
		start++;
	while (p->map.map[pos][end] == ' ')
		end--;
	while (start < end)
	{
		if (p->map.map[pos][start] != '1' && p->map.map[pos][start] != ' ')
			ft_error("MAP INVALID", "");
		start++;
	}
}

void	maperr(t_parcing *p)
{
	int		x;
	int		y;
	char	**tmp;

	x = 0;
	y = 0;
	while (p->map.map[x] != NULL)
	{
		y = 0;
		tmp = ft_split(p->map.map[x], ' ');
		while (tmp[y] != NULL)
		{
			if ((tmp[y][0] != '1' && tmp[y][0] != ' ') ||
			(tmp[y][ft_strlen(tmp[y]) - 1] != '1' &&
			tmp[y][ft_strlen(tmp[y]) - 1] != ' '))
			{
				ft_error("MAP INVALID", "");
			}
			y++;
		}
		x++;
		table_free(tmp);
	}
}

void	mapcheck(t_parcing *p, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < p->map.nbr_cols)
	{
		i = 0;
		while (i < p->map.nbr_rows)
		{
			if (tab[i][j] == ' ')
			{
				if (i > 0)
					if (tab[i - 1][j] != '1' && tab[i - 1][j] != ' ')
						ft_error("MAP INVALID", "");
				if (i < p->map.nbr_rows - 1)
					if (tab[i + 1][j] != '1' && tab[i + 1][j] != ' ')
						ft_error("MAP INVALID", "");
			}
			i++;
		}
		j++;
	}
}

void	map_out_line(t_parcing *p)
{
	map_out_up_down(p, 0);
	map_out_up_down(p, p->map.nbr_rows - 1);
	maperr(p);
	mapcheck(p, p->map.map);
}
