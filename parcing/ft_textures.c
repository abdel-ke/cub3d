/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:00:06 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/10 19:32:46 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		ft_check_textures(char *line)
{
	if ((line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		|| (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		|| (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		|| (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		|| (line[0] == 'S' && line[1] == ' '))
		return (TRUE);
	return (FALSE);
}

int		check_space(char *line)
{
	int i;

	i = 0;
	while (line[i++] == ' ')
		;
	return (i);
}

char	*ft_get_texture(char *line, int n)
{
	char	*path;
	int		start;
	int		end;
	int		i;

	start = n;
	i = 0;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	end = ft_strlen(line) - 1;
	while (line[end] == ' ' || line[end] == '\t')
		end--;
	path = malloc(sizeof(char) * (end++ - start) + 2);
	while (start < end)
		path[i++] = line[start++];
	path[i] = '\0';
	if (open(path, O_RDONLY) == -1 || path[i - 1] != 'm' ||
	path[i - 2] != 'p' || path[i - 3] != 'x')
		ft_error("PATH INVALID\t", path);
	return (path);
}

void	ft_check_texture(t_parcing *p, char *line)
{
	p->file_args++;
	if (line[0] == 'S' && line[1] == 'O' && !p->south)
		p->south = ft_get_texture(line, 2);
	else if (line[0] == 'N' && !p->north)
		p->north = ft_get_texture(line, 2);
	else if (line[0] == 'W' && !p->west)
		p->west = ft_get_texture(line, 2);
	else if (line[0] == 'E' && line[1] == 'A' && !p->east)
		p->east = ft_get_texture(line, 2);
	else if (line[0] == 'S' && line[1] == ' ' && !p->s_path)
		p->s_path = ft_get_texture(line, 1);
}
