/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 19:15:48 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/11 19:34:17 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_free2(t_data *d)
{
	if (d->parse.south != NULL)
		free(d->parse.south);
	if (d->parse.north != NULL)
		free(d->parse.north);
	if (d->parse.east != NULL)
		free(d->parse.east);
	if (d->parse.west != NULL)
		free(d->parse.west);
	if (d->parse.s_path != NULL)
		free(d->parse.s_path);
	if (d->parse.map.str != NULL)
		free(d->parse.map.str);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int		c_split(char const *str, char c)
{
	int	i;
	int cp_word;
	int is_num;

	is_num = 0;
	cp_word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			is_num = 0;
		else
		{
			if (is_num == 0)
			{
				cp_word++;
				is_num = 1;
			}
		}
		i++;
	}
	return (cp_word);
}

void	err_handler(int ac, char **av, t_parcing *p)
{
	char	**splited;
	char	*ext;

	p->handle = 0;
	if (ac == 1 || ac > 3)
		ft_error("CHECK ARG", "");
	splited = ft_split(av[1], '.');
	ext = splited[c_split(av[1], '.') - 1];
	if (ft_strcmp(ext, "cub") != 0)
		ft_error("CHECK ARG .CUB", "");
	if (open(av[1], O_RDONLY) == -1)
		ft_error("CHECK ARG", "");
	if (ac == 3)
	{
		if (ft_strcmp(av[2], "--save") != 0)
			ft_error("CHECK ARG SAVE", "");
		else
			p->handle = 1;
	}
	table_free(splited);
	ft_parse(p, av, 1);
}

int		keyrealease(int key, t_data *d)
{
	if (key == W_KEY || key == S_KEY)
		d->p.walk_dir = 0;
	if (key == D_KEY || key == A_KEY)
		d->p.st_side = 0;
	if (key == LEFT_KEY || key == RIGHT_KEY)
		d->p.turn_dir = 0;
	return (0);
}
