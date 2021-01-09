/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:32:21 by ymarji            #+#    #+#             */
/*   Updated: 2021/01/04 17:33:32 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_str;
	char	*src_str;


	dst_str = (char *)dst;
	src_str = (char *)src;
	i = 0;
	if (dst_str == NULL && src_str == NULL)
		return (NULL);
	while (n != 0)
	{
		dst_str[i] = src_str[i];
		i++;
		--n;
	}
	return (dst);
}
