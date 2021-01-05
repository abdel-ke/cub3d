/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 16:32:47 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/01/03 16:32:48 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static	void		ft_free(char **tab, int i)
{
	while (i)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

static int			count_word(char const *s, char c)
{
	int i;
	int pos;
	int count;

	i = 0;
	pos = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			pos = 0;
		else
		{
			if (pos == 0)
				count++;
			pos = 1;
		}
		i++;
	}
	return (count);
}

static	char		*put_word(char const *s, char c, int *n)
{
	int		i;
	int		first;
	int		last;
	char	*word;

	i = *n;
	while (s[i] == c)
		i++;
	first = i;
	while (s[i] != c && s[i])
		i++;
	last = i;
	word = (char *)malloc(sizeof(char) * (last - first + 1));
	if (!word)
		return (NULL);
	*n = i;
	i = 0;
	while (first < last)
		word[i++] = s[first++];
	word[i] = '\0';
	return (word);
}

char				**ft_split(char const *s, char c)
{
	char		**rslt;
	int			i;
	int			count;
	int			count_w;

	if (!s)
		return (0);
	if (!(rslt = (char **)malloc(sizeof(char*) * (count_word(s, c) + 1))))
		return (NULL);
	count = 0;
	i = 0;
	count_w = count_word(s, c);
	while (count < count_w)
		if (!(rslt[count++] = put_word(s, c, &i)))
		{
			ft_free(rslt, i);
			return (NULL);
		}
	rslt[count] = NULL;
	return (rslt);
}
