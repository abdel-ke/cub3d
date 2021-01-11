/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parcing_map_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:20:48 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/11 12:24:42 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		mapsearsh(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

int		map_is_last(t_parcing *p)
{
	if (p->p_w == -404 || p->p_h == -404 || p->s_path == NULL ||
	p->west == NULL || p->south == NULL || p->north == NULL
	|| p->east == NULL || !ft_check_color(p))
		return (TRUE);
	return (FALSE);
}

void ft_free2(t_parcing *p)
{
	if (p->south != NULL)
		free(p->south);
	if (p->north != NULL)
		free(p->north);
	if (p->east != NULL)
		free(p->east);

	if (p->west != NULL)
		free(p->west);

	if (p->s_path != NULL)
		free(p->s_path);
	if (p->map.str != NULL)
		free(p->map.str);
}
void	ft_stock_map(t_parcing *p, char *line)
{
	int	size;

	if (map_is_last(p))
	{
		ft_free2(p);
		ft_error("MAP IS NOT LAST AT FILE", "");
	}
	p->map.nbr_rows++;
	if ((size = ft_strlen(line)) > p->map.nbr_cols)
		p->map.nbr_cols = size;
	p->map.str = ft_strjoin_2(p->map.str, line, "@");
}

int		countrow(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

void	ft_check_map(t_parcing *p)
{
	char	*tmp;
	int		i;
	int		j;
	int		x;

	p->map.map = ft_split(p->map.str, '@');
	i = 0;
	while (p->map.map[i])
	{
		j = ft_strlen(p->map.map[i]);
		if (j < p->map.nbr_cols)
		{
			tmp = p->map.map[i];
			p->map.map[i] = (char *)malloc(sizeof(char) * p->map.nbr_cols + 2);
			x = -1;
			while (tmp[++x])
				p->map.map[i][x] = tmp[x];
			while (j < p->map.nbr_cols)
				p->map.map[i][j++] = ' ';
		}
		p->map.map[i][j] = '\0';
		i++;
	}
	free(tmp);
}
