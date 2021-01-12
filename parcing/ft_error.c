/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:06:12 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/12 18:12:08 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_putchar(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int		ft_error(char *str, char *str2)
{
	ft_putchar("ERROR\n");
	ft_putchar(str);
	ft_putchar(str2);
	ft_putchar("\n");
	exit(0);
}

void	table_free(char **tab)
{
	int i;
	int count;

	count = countrow(tab);
	i = 0;
	while (i < count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
