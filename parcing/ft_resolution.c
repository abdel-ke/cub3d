/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:07:31 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/11 19:30:17 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_check_r(char *line)
{
	char	**str;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strtrim(line, " ");
	str = ft_split(tmp, ' ');
	free(tmp);
	while (str[i])
		i++;
	if (i != 2)
	{
		table_free(str);
		ft_error("CHECK YOUR RESOLUTION\n", "");
	}
	table_free(str);
}

void	ft_get_resol(t_parcing *p, char *line)
{
	p->file_args++;
	ft_check_r(line);
	while (*line == ' ')
		line++;
	p->p_w = ft_atoi(line) >= INT_MAX ? 1440 : ft_atoi(line);
	while ((*line >= '0' && *line <= '9'))
		line++;
	p->p_h = ft_atoi(line) >= INT_MAX ? 2560 : ft_atoi(line);
	p->p_w = p->p_w > 2560 ? 2560 : p->p_w;
	p->p_h = p->p_h > 1440 ? 1440 : p->p_h;
	if (p->p_w <= 0 || p->p_h <= 0)
		ft_error("CHECK YOUR RESOLUTION", "");
}
