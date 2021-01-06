/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:28:15 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/06 15:33:03 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	initial_color(t_parcing *p)
{
	int i;

	i = -1;
	while (i++)
	{
		p->c[i].r = -404;
		p->c[i].g = -404;
		p->c[i].b = -404;
		p->c[i].color = -404;
	}
}

void	initial(t_parcing *p)
{
	p->p_w = -404;
	p->p_h = -404;
	p->south = NULL;
	p->north = NULL;
	p->east = NULL;
	p->west = NULL;
	p->s_path = NULL;
	p->map.str = ft_strdup("");
	p->map.nbr_cols = 0;
	p->map.nbr_rows = 0;
	p->file_args = 0;
	initial_color(p);
}

void	ft_parse(t_parcing *p, int ac, char **av)
{
	int		fd;
	char	*line;

	initial(p);
	if ((fd = open(av[1], O_RDONLY)) == -1 || ac < 1)
		ft_putchar("check arguments\n");
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == ' ' && p->file_args != 8)
		{
			// printf("|%d|\n", p->file_args);
			ft_putchar(line);
			ft_error("\nARG INVALID");
		}
		else if (line[0] == 'R' && line[1] == ' ')
			ft_get_resol(p, line + 2);
		else if (ft_check_textures(line))
			ft_check_texture(p, line);
		else if ((line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
			ft_get_color(p, line);
		else if (mapsearsh(line))
			ft_stock_map(p, line);
	}
	ft_check_map(p);
	map_out_line(p);
}
