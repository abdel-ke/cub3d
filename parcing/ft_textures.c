/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:00:06 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/03 17:29:58 by abdel-ke         ###   ########.fr       */
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

char	*ft_get_texture(char *line)
{
	int		len;
	char	*path;

	path = ft_strdup(&line[check_space(line + 2)]);
	len = ft_strlen(path) - 1;
	while (line[len] == ' ' || line[len] == '\t')
		len--;
	if (open(path + 3, O_RDONLY) == -1 || path[len] != 'm' ||
	path[len - 1] != 'p' || path[len - 2] != 'x')
	{
		ft_putchar(path);
		ft_error("\nPATH INVALID\n");
		free(path);
	}
	return (path);
}

void	ft_check_texture(t_parcing *p, char *line)
{
	p->file_args++;
	if (line[0] == 'S' && line[1] == 'O' && !p->south)
		p->south = ft_get_texture(line);
	else if (line[0] == 'N' && !p->north)
		p->north = ft_get_texture(line);
	else if (line[0] == 'W' && !p->west)
		p->west = ft_get_texture(line);
	else if (line[0] == 'E' && line[1] == 'A' && !p->east)
		p->east = ft_get_texture(line);
	else if (line[0] == 'S' && line[1] == ' ' && !p->s_path)
		p->s_path = ft_get_texture(line);
}
